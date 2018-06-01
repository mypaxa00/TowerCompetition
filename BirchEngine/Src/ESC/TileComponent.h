#pragma once

#include "Components.h"
#include <SDL.h>

enum TileID
{
	//Main
	T_Dirt, T_Grass, T_Road, T_Sand,
	T_Dirt_c, T_Grass_c, T_Road_c, T_Sand_c,
	//Dirt
	T_DirtSmGrassDL, T_DirtGrassD, T_DirtSmGrassDR,
	T_DirtBgGrassUL, T_DirtBgGrassUR,
	T_DirtSmSandDL, T_DirtSandD, T_DirtSmSandDR,
	T_DirtBgSandUL, T_DirtBgSandUR,
	T_DirtSmRoadDL, T_DirtRoadD, T_DirtSmRoadDR,
	T_DirtBgRoadUL, T_DirtBgRoadUR,
	T_DirtGrassR, T_DirtGrassL, T_DirtBgGrassDL, T_DirtBgGrassDR,
	T_DirtSandR, T_DirtSandL, T_DirtBgSandDL, T_DirtBgSandDR,
	T_DirtRoadR, T_DirtRoadL, T_DirtBgRoadDL, T_DirtBgRoadDR,
	T_DirtSmGrassUL, T_DirtGrassU, T_DirtSmGrassUR, T_DirtMdGrass,
	T_DirtSmSandUL, T_DirtSandU, T_DirtSmSandUR, T_DirtMdSand,
	T_DirtSmRoadUL, T_DirtRoadU, T_DirtSmRoadUR, T_DirtMdRoad,
	//Grass
	T_GrassSmDirtDL, T_GrassDirtD, T_GrassSmDirtDR,
	T_GrassBgDirtUL, T_GrassBgDirtUR,
	T_GrassSmSandDL, T_GrassSandD, T_GrassSmSandDR,
	T_GrassBgSandUL, T_GrassBgSandUR,
	T_GrassSmRoadDL, T_GrassRoadD, T_GrassSmRoadDR,
	T_GrassBgRoadUL, T_GrassBgRoadUR,
	T_GrassDirtR, T_GrassDirtL, T_GrassBgDirtDL, T_GrassBgDirtDR,
	T_GrassSandR, T_GrassSandL, T_GrassBgSandDL, T_GrassBgSandDR,
	T_GrassRoadR, T_GrassRoadL, T_GrassBgRoadDL, T_GrassBgRoadDR,
	T_GrassSmDirtUL, T_GrassDirtU, T_GrassSmDirtUR, T_GrassMdDirt,
	T_GrassSmSandUL, T_GrassSandU, T_GrassSmSandUR, T_GrassMdSand,
	T_GrassSmRoadUL, T_GrassRoadU, T_GrassSmRoadUR, T_GrassMdRoad,
	//Sand
	T_SandSmGrassDL, T_SandGrassD, T_SandSmGrassDR,
	T_SandBgGrassUL, T_SandBgGrassUR,
	T_SandSmDirtDL, T_SandDirtD, T_SandSmDirtDR,
	T_SandBgDirtUL, T_SandBgDirtUR,
	T_SandSmRoadDL, T_SandRoadD, T_SandSmRoadDR,
	T_SandBgRoadUL, T_SandBgRoadUR,
	T_SandGrassR, T_SandGrassL, T_SandBgGrassDL, T_SandBgGrassDR,
	T_SandDirtR, T_SandDirtL, T_SandBgDirtDL, T_SandBgDirtDR,
	T_SandRoadR, T_SandRoadL, T_SandBgRoadDL, T_SandBgRoadDR,
	T_SandSmGrassUL, T_SandGrassU, T_SandSmGrassUR, T_SandMdGrass,
	T_SandSmDirtUL, T_SandDirtU, T_SandSmDirtUR, T_SandMdDirt,
	T_SandSmRoadUL, T_SandRoadU, T_SandSmRoadUR, T_SandMdRoad,
	//Road
	T_RoadSmGrassDL, T_RoadGrassD, T_RoadSmGrassDR,
	T_RoadBgGrassUL, T_RoadBgGrassUR,
	T_RoadSmDirtDL, T_RoadDirtD, T_RoadSmDirtDR,
	T_RoadBgDirtUL, T_RoadBgDirtUR,
	T_RoadSmSandDL, T_RoadSandD, T_RoadSmSandDR,
	T_RoadBgSandUL, T_RoadBgSandUR,
	T_RoadGrassR, T_RoadGrassL, T_RoadBgGrassDL, T_RoadBgGrassDR,
	T_RoadDirtR, T_RoadDirtL, T_RoadBgDirtDL, T_RoadBgDirtDR,
	T_RoadSandR, T_RoadSandL, T_RoadBgSandDL, T_RoadBgSandDR,
	T_RoadSmGrassUL, T_RoadGrassU, T_RoadSmGrassUR, T_RoadMdGrass,
	T_RoadSmDirtUL, T_RoadDirtU, T_RoadSmDirtUR, T_RoadMdDirt,
	T_RoadSmSandUL, T_RoadSandU, T_RoadSmSandUR, T_RoadMdSand,
	//Decorations
	D_RockS, D_RockM, D_RockB,
	D_ShrubCloudB, D_ShrubCloudS,
	D_ShrubLeavsB, D_ShrubLeavsS,
	D_ShrubRound, D_CraterRound, D_CraterDrops, D_CraterBang,
	//Tower places
	P_Dirt, P_Grass, P_Sand, P_Road

};

class TileComponent : public Component
{
public:
	TransformComponent * transform;
	SpriteComponent * sprite;
	
	SDL_Rect tileRect;
	TileID tileID;
	std::string path;

	TileComponent() = default;

	TileComponent(int id, int x, int y, int w = 64, int h = 64) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = (TileID)id;

		switch (tileID)
		{
		case 1000:
			break;
		default:
			path = std::to_string(tileID);
			break;
		}
	}

	void init() override {
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}

private:

};

