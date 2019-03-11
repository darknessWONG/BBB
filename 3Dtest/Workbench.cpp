#include "stdafx.h"
#include "Workbench.h"
#include "ItemFactory.h"
#include "input.h"
#include "Common.h"
#include "Recipe.h"
#include "gamepad.h"

int** Workbench::recipe = NULL;
int Workbench::recipeNum = 0;

Workbench::Workbench(int line, int column, float width, float length)
{
	this->lineNum = line;
	this->columnNum = column;
	this->width = width;
	this->length = length;

	int vertexNum = ((lineNum + 1) + (columnNum + 1)) * 2;
	grid = new Vertex[vertexNum];

	for (int i = -width / 2, j = 0, k = length / 2;
		i <= width / 2 || k >= -length / 2; 
		i += width / (columnNum), k -= length / (lineNum), j += 2)
	{
		grid[j].position = D3DXVECTOR3(i, 0, length / 2);
		grid[j].color = 0xFFFF0000;
		//grid[j].texPos = D3DXVECTOR2(j / (columnNum + 1), 0);

		grid[j + 1].position = D3DXVECTOR3(i, 0, -length / 2);
		grid[j + 1].color = 0xFFFF0000;
		//grid[j + 1].texPos = D3DXVECTOR2(j / (columnNum + 1), 1);

		grid[vertexNum - 1 - j].position = D3DXVECTOR3(-width / 2, 0, k);
		grid[vertexNum - 1 - j].color = 0xFFFF0000;
		//grid[vertexNum - 1 - j].texPos = D3DXVECTOR2(0, j / (lineNum + 1));

		grid[vertexNum - 1 - (j + 1)].position = D3DXVECTOR3(width / 2, 0, k);
		grid[vertexNum - 1 - (j + 1)].color = 0xFFFF0000;
		//grid[vertexNum - 1 - (j + 1)].texPos = D3DXVECTOR2(1, j / (lineNum + 1));
	}

	items = new Item*[lineNum * columnNum]{NULL};
}


Workbench::~Workbench()
{
	safe_delete<Item*>(items);
	safe_delete<Vertex>(grid);
	delete[] recipe;

}

void Workbench::draw(LPDIRECT3DDEVICE9 pD3DDevice)
{
	pD3DDevice->SetFVF(FVF_VERTEX3D);

	pD3DDevice->SetTransform(D3DTS_WORLD, getMtxWorld()); //set the world matrix to the device
	pD3DDevice->SetTexture(0, NULL);


	pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, (lineNum + 1) + (columnNum + 1), grid, sizeof(Vertex));
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}

void Workbench::dataUpdate(void)
{
	if (Keyboard_IsTrigger(DIK_J) || Gamepad_isTrigger(XINPUT_GAMEPAD_B))
	{
		fuseItems();
	}
}

RECTF Workbench::getBoundingRect(void)
{
	RECTF rect;
	rect.top = getVecNowPos()->z + length / 2;
	rect.bottom = getVecNowPos()->z - length / 2;
	rect.right = getVecNowPos()->x + width / 2;
	rect.left = getVecNowPos()->x - width / 2;
	return rect;
}

D3DXVECTOR2 Workbench::getBoundingCenter(void)
{
	D3DXVECTOR3 *center = getVecNowPos();
	return D3DXVECTOR2{center->x, center->z};
}

void Workbench::setBoundingCenter(D3DXVECTOR2 center)
{
	D3DXVECTOR3 nowPos = *getVecNowPos();
	nowPos.x = center.x;
	nowPos.z = center.y;
	setVecNowPos(&nowPos);
}

bool Workbench::addItem(Item* item)
{
	D3DXVECTOR2 itemCenter = item->getBoundingCenter();
	D3DXVECTOR2 center = getBoundingCenter();
	center.x -= width / 2;
	center.y += length / 2;
	itemCenter -= center;
	int x = abs(itemCenter.x *  columnNum / width);
	int y = abs(itemCenter.y * lineNum / length);

	if (items[y * columnNum + x] == NULL)
	{
		items[y * columnNum + x] = item;
		//item->setBelong(this);
		return true;
	}
	else
	{
		return false;
	}
}

void Workbench::releaseItems(void)
{
	int itemNum = lineNum * columnNum;
	for (int i = 0; i < itemNum; i++)
	{
		items[i] = NULL;
	}
}

void Workbench::fuseItems(void)
{
	int itemNum = lineNum * columnNum;
	bool isFuse = false;
	int i = 0;
	for (i = 0; i < Workbench::recipeNum; i++)
	{
		int j = 0;
		for (j = 0; j < itemNum; j++)
		{
			if ((items[j] == NULL && recipe[i][j] != -1))
			{
				break;
			}
			else if (items[j] != NULL && (items[j]->getStatusNow() != recipe[i][j]))
			{
				break;
			}
		}
		if (j == itemNum)
		{
			isFuse = true;
			break;
		}
	}
	if (isFuse)
	{
		bool fused = false;
		for (int j = 0; j < itemNum; j++)
		{
			if (items[j] != NULL)
			{
				if (!fused)
				{
					
					//items[j]->setStatusNow(recipe[i][itemNum]);
					ItemFactory::setItemStatus(items[j], (ResourceM)recipe[i][itemNum]);
					items[j]->setBoundingCenter(getBoundingCenter());
					fused = true;
				}
				else
				{
					items[j]->setIsDestory(true);
				}
			}
		}
		/*for (int j = 0; j < itemNum; j++)
		{
			items[j]->setIsDestory(true);
		}
		return ItemFactory::create_item(getBoundingCenter().x, getBoundingCenter().y, recipe[i][itemNum]);*/
	}

	releaseItems();
}

D3DXVECTOR2 Workbench::calBolckPosition(D3DXVECTOR2 block)
{
	D3DXVECTOR2 result;
	D3DXVECTOR2 center = getBoundingCenter();
	center.x -= width / 2;
	center.y += length / 2;

	result.x = center.x + (width / columnNum * block.x) + width / columnNum / 2;
	result.y = center.y - (length / lineNum * block.y) - length / lineNum / 2;
	return result;
}

void Workbench::setItemsPosition(void)
{
	int itemNum = lineNum * columnNum;
	for (int i = 0; i < lineNum; i++)
	{
		for (int j = 0; j < columnNum; j++)
		{
			if (items[i * columnNum + j] != NULL)
			{
				D3DXVECTOR2 new_pos = calBolckPosition({ (float)j, (float)i });
				items[i * columnNum + j]->setBoundingCenter(new_pos);
			}
		}
	}

}

int Workbench::getLineNum(void)
{
	return lineNum;
}

void Workbench::setLineNum(int lineNum)
{
	this->lineNum = lineNum;
}

int Workbench::getColumnNum(void)
{
	return columnNum;
}

void Workbench::setColumnNum(int columnNum)
{
	this->columnNum = columnNum;
}

float Workbench::getWidth(void)
{
	return width;
}

void Workbench::setWidth(float width)
{
	this->width = width;
}

float Workbench::getLength(void)
{
	return length;
}

void Workbench::setLength(float length)
{
	this->length = length;
}

void Workbench::initRecipe(void)
{
	recipeNum = 4;
	recipe = new int*[recipeNum];
	recipe[0] = new int[10]{
		ResourceM::RESOURCEM_WOOD,		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_BRICK,
		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_BRICK,		ResourceM::RESOURCEM_IRON,
		ResourceM::RESOURCEM_IRON,		ResourceM::RESOURCEM_WOOD,		ResourceM::RESOURCEM_NONE,
	3};
	recipe[1] = new int[10]{
		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_IRON,
		ResourceM::RESOURCEM_IRON,		ResourceM::RESOURCEM_IRON,		ResourceM::RESOURCEM_WOOD,
		ResourceM::RESOURCEM_WOOD,		ResourceM::RESOURCEM_WOOD,		ResourceM::RESOURCEM_BRICK,
	4};
	recipe[2] = new int[10]{
		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_BRICK,		ResourceM::RESOURCEM_NONE,
		ResourceM::RESOURCEM_IRON,		ResourceM::RESOURCEM_BRICK,		ResourceM::RESOURCEM_IRON,
		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_IRON,		ResourceM::RESOURCEM_NONE,
	5 };
	recipe[3] = new int[10]{
		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_IRON,		ResourceM::RESOURCEM_NONE,
		ResourceM::RESOURCEM_WOOD,		ResourceM::RESOURCEM_NONE,		ResourceM::RESOURCEM_WOOD,
		ResourceM::RESOURCEM_WOOD,		ResourceM::RESOURCEM_WOOD,		ResourceM::RESOURCEM_WOOD,
	6};
}