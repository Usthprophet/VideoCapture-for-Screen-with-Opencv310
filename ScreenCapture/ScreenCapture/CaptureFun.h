#pragma once

//�������صĺ���

cv::Mat initGDI(POINT q,POINT p)			//�����������ֽ�ͼ��ȡ
{

	int nWidth = p.x;
	int nHeight = p.y;

	int aWidth = q.x;
	int aHeight = q.y;


	LPVOID screenCaptureData = new char[nWidth*nHeight * 4];		//���ڽ���������ʢװ������
	memset(screenCaptureData, 0, nWidth);
	// Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.
	HDC hDDC = GetDC(GetDesktopWindow());//�õ���Ļ��dc
	HDC hCDC = CreateCompatibleDC(hDDC);//
	HBITMAP hBitmap = CreateCompatibleBitmap(hDDC, nWidth, nHeight);//�õ�λͼ
	SelectObject(hCDC, hBitmap); //�����ܵ���ôд��

	BitBlt(hCDC, 0, 0, nWidth- aWidth, nHeight- aHeight, hDDC, aWidth, aHeight, SRCCOPY);

	GetBitmapBits(hBitmap, nWidth*nHeight * 4, screenCaptureData);//�õ�λͼ�����ݣ����浽screenCaptureData�����С�
	IplImage *img = cvCreateImage(cvSize(nWidth, nHeight), 8, 4);//����һ��rgba��ʽ��IplImage
	memcpy(img->imageData, screenCaptureData, nWidth*nHeight * 4);//�����Ƚ��˷�ʱ�䣬��д�ķ��㡣����������*4�����������д����*3�����ǲ��Եġ�
	IplImage *img2 = cvCreateImage(cvSize(nWidth, nHeight), 8, 3);//����һ��bgr��ʽ��IplImage������û�����Img2���������
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

cv::Mat initGDI(POINT pointer)			//��һ��������Ϊ��0.0����ʼ
{
	POINT poi;
	poi.x = poi.y = 0;
	return initGDI(poi,pointer);
}

cv::Mat initGDI()			//��������,��ȫ��ȡ
{
	int nWidth = GetSystemMetrics(SM_CXSCREEN);//�õ���Ļ�ķֱ��ʵ�x
	int nHeight = GetSystemMetrics(SM_CYSCREEN);//�õ���Ļ�ֱ��ʵ�y
	POINT pointer;
	pointer.x = nWidth;
	pointer.y = nHeight;
	return initGDI(pointer);
}
