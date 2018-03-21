#pragma once

//与截屏相关的函数

cv::Mat initGDI(POINT q,POINT p)			//带参数，部分截图截取
{

	int nWidth = p.x;
	int nHeight = p.y;

	int aWidth = q.x;
	int aHeight = q.y;


	LPVOID screenCaptureData = new char[nWidth*nHeight * 4];		//用于截屏的数据盛装的类型
	memset(screenCaptureData, 0, nWidth);
	// Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.
	HDC hDDC = GetDC(GetDesktopWindow());//得到屏幕的dc
	HDC hCDC = CreateCompatibleDC(hDDC);//
	HBITMAP hBitmap = CreateCompatibleBitmap(hDDC, nWidth, nHeight);//得到位图
	SelectObject(hCDC, hBitmap); //好像总得这么写。

	BitBlt(hCDC, 0, 0, nWidth- aWidth, nHeight- aHeight, hDDC, aWidth, aHeight, SRCCOPY);

	GetBitmapBits(hBitmap, nWidth*nHeight * 4, screenCaptureData);//得到位图的数据，并存到screenCaptureData数组中。
	IplImage *img = cvCreateImage(cvSize(nWidth, nHeight), 8, 4);//创建一个rgba格式的IplImage
	memcpy(img->imageData, screenCaptureData, nWidth*nHeight * 4);//这样比较浪费时间，但写的方便。这里必须得是*4，上面的链接写的是*3，这是不对的。
	IplImage *img2 = cvCreateImage(cvSize(nWidth, nHeight), 8, 3);//创建一个bgr格式的IplImage，可以没有这个Img2这个变量。
	cvCvtColor(img, img2, CV_BGRA2BGR);
	cv::Mat MatImg = cv::cvarrToMat(img2).clone();

	cvReleaseImage(&img);
	cvReleaseImage(&img2);
	DeleteDC(hDDC);
	DeleteDC(hCDC);
	DeleteObject(hBitmap);
	delete(screenCaptureData);


	return MatImg;
}

cv::Mat initGDI(POINT pointer)			//带一个参数则为（0.0）开始
{
	POINT poi;
	poi.x = poi.y = 0;
	return initGDI(poi,pointer);
}

cv::Mat initGDI()			//不带参数,完全截取
{
	int nWidth = GetSystemMetrics(SM_CXSCREEN);//得到屏幕的分辨率的x
	int nHeight = GetSystemMetrics(SM_CYSCREEN);//得到屏幕分辨率的y
	POINT pointer;
	pointer.x = nWidth;
	pointer.y = nHeight;
	return initGDI(pointer);
}
