#define _AFXDLL//为了方便是用mfc类
#include<afxwin.h>
#include<opencv2\opencv.hpp>
#include<iostream>
#include"CaptureFun.h"
#include"MouseHandle.h"

void ViewManu()
{
	std::cout << "type the Capital symbol or full name to use the function:\n"
		<< "Full		------------ Videoing as Full Screen\n"
		<< "Custom		———————Videoing by a ruled size manully\n";
}

void ViewCustomed()
{
	std::cout << "how many Point?:";
	int fuck;
	std::cin >> fuck;
	if (fuck == 1)
	{
		std::cout << "type two number as its x and y:\n";
		POINT pointer;
		std::cin >> pointer.x >> pointer.y;
		while (1)
		{
			cv::Mat fu = initGDI(pointer);
			cv::imshow("Video", fu);
			cv::waitKey(10);
		}
	}
	else if (fuck == 2)
	{
		std::cout << "For number is required as two point\n";
		POINT pointerX;
		POINT pointerY;
		std::cin >> pointerX.x >> pointerX.y >> pointerY.x >> pointerY.y;
		while (1)
		{
			cv::Mat fu = initGDI(pointerX,pointerY);
			cv::imshow("Video", fu);
			cv::waitKey(10);
		}
	}
	else std::cout << "A wrong Number ,go back automatic\n";
}


int main()
{

	ViewManu();
	std::string Command;
	
	while (std::cin >> Command)
	{
		if (Command == "full" || Command == "Full" || Command == "F")
		{
			while (1)
			{
				cv::Mat fu = initGDI();
				cv::imshow("Video", fu);
				cv::waitKey(10);
			}
		}
		else if (Command == "Custom" || Command == "custom" || Command == "c")
		{
			ViewCustomed();
		}
		else std::cout << "A wrong function ,input again\n";
	}

}