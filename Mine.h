#pragma once
#ifndef _MINE_
#define _MINE_

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _CSTRING_
#include <cstring>
#endif

#ifndef _SET_
#include <set>
#endif

#ifndef _QUEUE_
#include <queue>
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef _STACK_
#include <stack>
#endif

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

#ifndef _INC_TIME
#include <time.h>
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

class GameMap {
	int width;			//宽度
	int height;			//长度
	bool isLose;		//是否失败
	int unshownfileds;	//未被探测的区域
	std::vector<std::vector<int>>MineMap;	//地雷图
	std::vector<std::vector<bool>>showMap;	//是否被探测
	int aroundPos[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };	//八个方向
	class Point {
	public:
		int x;
		int y;
		Point() { x = 0; y = 0; };
		Point(int x, int y) :x(x), y(y) {};
		bool operator < (Point a)const {
			if (x == a.x) return y < a.y;
			return x < a.x;
		}
	};	//坐标
public:
	GameMap() { width = 1; height = 1; isLose = false; unshownfileds = 1; };
	GameMap(int width, int height) :width(width), height(height), isLose(false), unshownfileds(width* height) {};
	void initMap(int Width, int Height, int mineCnt, unsigned int seed = (unsigned)time(NULL)) {
		if (Width * Height < mineCnt) throw "Area Too Small!";
		width = Width;
		height = Height;
		unshownfileds = Width * Height - mineCnt;
		std::vector<std::vector<int>>(Height + 1, std::vector<int>(Width + 1, 0)).swap(MineMap);
		std::vector<std::vector<bool>>(Height + 1, std::vector<bool>(Width + 1, false)).swap(showMap);
		srand(seed);
		std::set<Point>MinePos;
		while (MinePos.size() < mineCnt) {
			srand((unsigned)(rand() + time(NULL)));
			int x = rand() % height + 1;
			srand((unsigned)(rand() + time(NULL)));
			int y = rand() % width + 1;
			MinePos.insert(Point(x, y));
		}
		for (auto& Mine : MinePos) {
			MineMap[Mine.x][Mine.y] = -1;
			for (int i = 0; i < 8; i++) {
				int nx = Mine.x + aroundPos[i][0], ny = Mine.y + aroundPos[i][1];
				if (nx < 1 || nx > height || ny < 1 || ny > width) continue;
				if (MineMap[nx][ny] != -1) MineMap[nx][ny]++;
			}
		}
	}	//初始化一张图
	void printMap() {
		for (int i = 1; i <= height; i++, std::cout << std::endl)
			for (int j = 1; j <= width; j++) {
				if (!showMap[i][j] && !isLose) {
					std::cout << ". ";
					continue;
				}
				if (MineMap[i][j] == -1) std::cout << "* ";
				else std::cout << MineMap[i][j] << " ";
			}
	}	//打印当前的地图
	int detectMap(int x, int y) {
		if (x <= 0 || x > height || y <= 0 || y > width) return 0;
		if (showMap[x][y]) return 0;
		if (!showMap[x][y]) {
			showMap[x][y] = true;
			unshownfileds--;
		}
		if (unshownfileds == 0) return 1;
		if (MineMap[x][y] == -1) { isLose = true; return -1; }
		if (MineMap[x][y] != 0) return 0;
		std::queue<Point>Qu;
		Qu.push(Point(x, y));
		while (!Qu.empty()) {
			Point u = Qu.front(); Qu.pop();
			if (!showMap[u.x][u.y]) {
				showMap[u.x][u.y] = true;
				unshownfileds--;
			}
			if (unshownfileds == 0) return 1;
			if (MineMap[u.x][u.y] != 0)	continue;
			for (int i = 0; i < 8; i++) {
				int nx = u.x + aroundPos[i][0], ny = u.y + aroundPos[i][1];
				if (nx < 1 || nx > height || ny < 1 || ny > width) continue;
				if (!showMap[nx][ny]) Qu.push(Point(nx, ny));
			}
		}
		return 0;
	}	//进行一次探测
};

#endif // !_MINE_
