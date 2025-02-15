
/*
	À­   : 0
	¾Æ·¡ : 1
	¾Õ   : 2
	µÚ   : 3
	¿Þ   : 4
	¿À   : 5
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <array>
#include <unordered_map>

using Plane = std::array<char, 9>;
using Cube = std::array<Plane, 6>;
using Rot = std::function<void()>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Cube cube;
	auto rotatePlaneCW = [](Plane *ppl)
		{
			char temp3 = (*ppl)[3];
			char temp6 = (*ppl)[6];

			(*ppl)[3] = (*ppl)[7];
			(*ppl)[6] = (*ppl)[8];
			(*ppl)[7] = (*ppl)[5];
			(*ppl)[8] = (*ppl)[2];
			(*ppl)[5] = (*ppl)[1];
			(*ppl)[2] = (*ppl)[0];
			(*ppl)[1] = temp3;
			(*ppl)[0] = temp6;
		};
	auto rotatePlaneCCW = [](Plane *ppl)
		{
			char temp0 = (*ppl)[0];
			char temp1 = (*ppl)[1];
			(*ppl)[0] = (*ppl)[2];
			(*ppl)[1] = (*ppl)[5];
			(*ppl)[2] = (*ppl)[8];
			(*ppl)[5] = (*ppl)[7];
			(*ppl)[8] = (*ppl)[6];
			(*ppl)[7] = (*ppl)[3];
			(*ppl)[6] = temp0;
			(*ppl)[3] = temp1;
		};
	auto rotate = [](Rot r,
		char *a, char *b, char *c,
		char *d, char *e, char *f,
		char *g, char *h, char *i,
		char *j, char *k, char *l)
		{
			char temp1 = *l;
			char temp2 = *k;
			char temp3 = *j;
			*l = *i;
			*k = *h;
			*j = *g;
			*i = *f;
			*h = *e;
			*g = *d;
			*f = *c;
			*e = *b;
			*d = *a;
			*c = temp1;
			*b = temp2;
			*a = temp3;
			r();
		};
	Rot rotPUCW = std::bind(rotatePlaneCW, &cube[0]);
	Rot rotPUCCW = std::bind(rotatePlaneCCW, &cube[0]);
	Rot rotPFCW = std::bind(rotatePlaneCW, &cube[2]);
	Rot rotPFCCW = std::bind(rotatePlaneCCW, &cube[2]);
	Rot rotPDCW = std::bind(rotatePlaneCW, &cube[1]);
	Rot rotPDCCW = std::bind(rotatePlaneCCW, &cube[1]);
	Rot rotPBCW = std::bind(rotatePlaneCW, &cube[3]);
	Rot rotPBCCW = std::bind(rotatePlaneCCW, &cube[3]);
	Rot rotPLCW = std::bind(rotatePlaneCW, &cube[4]);
	Rot rotPLCCW = std::bind(rotatePlaneCCW, &cube[4]);
	Rot rotPRCW = std::bind(rotatePlaneCW, &cube[5]);
	Rot rotPRCCW = std::bind(rotatePlaneCCW, &cube[5]);
	Rot rotUCW = std::bind(rotate, rotPUCW,
		&cube[3][6], &cube[3][7], &cube[3][8],
		&cube[5][2], &cube[5][1], &cube[5][0],
		&cube[2][2], &cube[2][1], &cube[2][0], 
		&cube[4][2], &cube[4][1], &cube[4][0]);
	Rot rotUCCW = std::bind(rotate, rotPUCCW,
		&cube[4][0], &cube[4][1], &cube[4][2],
		&cube[2][0], &cube[2][1], &cube[2][2], 
		&cube[5][0], &cube[5][1], &cube[5][2], 
		&cube[3][8], &cube[3][7], &cube[3][6]);
	Rot rotFCW = std::bind(rotate, rotPFCW,
		&cube[0][6], &cube[0][7], &cube[0][8],
		&cube[5][0], &cube[5][3], &cube[5][6], 
		&cube[1][2], &cube[1][1], &cube[1][0], 
		&cube[4][8], &cube[4][5], &cube[4][2]);
	Rot rotFCCW = std::bind(rotate, rotPFCCW,
		&cube[4][2], &cube[4][5], &cube[4][8],
		&cube[1][0], &cube[1][1], &cube[1][2], 
		&cube[5][6], &cube[5][3], &cube[5][0], 
		&cube[0][8], &cube[0][7], &cube[0][6]);
	Rot rotDCW = std::bind(rotate, rotPDCW,
		&cube[2][6], &cube[2][7], &cube[2][8],
		&cube[5][6], &cube[5][7], &cube[5][8], 
		&cube[3][2], &cube[3][1], &cube[3][0], 
		&cube[4][6], &cube[4][7], &cube[4][8]);
	Rot rotDCCW = std::bind(rotate, rotPDCCW,
		&cube[4][8], &cube[4][7], &cube[4][6],
		&cube[3][0], &cube[3][1], &cube[3][2], 
		&cube[5][8], &cube[5][7], &cube[5][6], 
		&cube[2][8], &cube[2][7], &cube[2][6]);
	Rot rotBCW = std::bind(rotate, rotPBCW,
		&cube[1][6], &cube[1][7], &cube[1][8],
		&cube[5][8], &cube[5][5], &cube[5][2], 
		&cube[0][2], &cube[0][1], &cube[0][0], 
		&cube[4][0], &cube[4][3], &cube[4][6]);
	Rot rotBCCW = std::bind(rotate, rotPBCCW,
		&cube[4][6], &cube[4][3], &cube[4][0],
		&cube[0][0], &cube[0][1], &cube[0][2], 
		&cube[5][2], &cube[5][5], &cube[5][8], 
		&cube[1][8], &cube[1][7], &cube[1][6]);
	Rot rotLCW = std::bind(rotate, rotPLCW,
		&cube[0][0], &cube[0][3], &cube[0][6],
		&cube[2][0], &cube[2][3], &cube[2][6], 
		&cube[1][0], &cube[1][3], &cube[1][6], 
		&cube[3][0], &cube[3][3], &cube[3][6]);
	Rot rotLCCW = std::bind(rotate, rotPLCCW,
		&cube[3][6], &cube[3][3], &cube[3][0],
		&cube[1][6], &cube[1][3], &cube[1][0], 
		&cube[2][6], &cube[2][3], &cube[2][0], 
		&cube[0][6], &cube[0][3], &cube[0][0]);
	Rot rotRCW = std::bind(rotate, rotPRCW,
		&cube[0][8], &cube[0][5], &cube[0][2],
		&cube[3][8], &cube[3][5], &cube[3][2], 
		&cube[1][8], &cube[1][5], &cube[1][2], 
		&cube[2][8], &cube[2][5], &cube[2][2]);
	Rot rotRCCW = std::bind(rotate, rotPRCCW,
		&cube[2][2], &cube[2][5], &cube[2][8],
		&cube[1][2], &cube[1][5], &cube[1][8], 
		&cube[3][2], &cube[3][5], &cube[3][8], 
		&cube[0][2], &cube[0][5], &cube[0][8]);

	std::unordered_map<std::string, Rot> queryHandler;
	queryHandler.insert(make_pair("U+", rotUCW));
	queryHandler.insert(make_pair("U-", rotUCCW));
	queryHandler.insert(make_pair("F+", rotFCW));
	queryHandler.insert(make_pair("F-", rotFCCW));
	queryHandler.insert(make_pair("D+", rotDCW));
	queryHandler.insert(make_pair("D-", rotDCCW));
	queryHandler.insert(make_pair("B+", rotBCW));
	queryHandler.insert(make_pair("B-", rotBCCW));
	queryHandler.insert(make_pair("L+", rotLCW));
	queryHandler.insert(make_pair("L-", rotLCCW));
	queryHandler.insert(make_pair("R+", rotRCW));
	queryHandler.insert(make_pair("R-", rotRCCW));

	auto printUpPlane = [&]()
		{
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					std::cout << cube[0][i * 3 + j];
				}
				std::cout << '\n';
			}
		};

	std::string query;
	int testNum, rotNum;
	std::cin >> testNum;
	while (testNum--)
	{
		std::fill(cube[0].begin(), cube[0].end(), 'w');
		std::fill(cube[1].begin(), cube[1].end(), 'y');
		std::fill(cube[2].begin(), cube[2].end(), 'r');
		std::fill(cube[3].begin(), cube[3].end(), 'o');
		std::fill(cube[4].begin(), cube[4].end(), 'g');
		std::fill(cube[5].begin(), cube[5].end(), 'b');
		std::cin >> rotNum;
		for (int i = 0; i < rotNum; ++i)
		{
			std::cin >> query;
			queryHandler[query]();
		}
		printUpPlane();
	}
}