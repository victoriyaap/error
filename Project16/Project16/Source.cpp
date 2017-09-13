#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/dir_nav.h>	
#include <opencv/highgui.h>
#include <opencv/cv.h>

#include <iostream>

using namespace std;
using namespace cv;
using namespace dlib;

void mouse_callback(int event, int x, int y, int flags, void* param);
CvRect box;
bool drawing_box = false;

//������� ��������� �������������� �� �����������
void draw_box(IplImage* img, CvRect rect) {
	cvRectangle(
		img,
		cvPoint(box.x, box.y),
		cvPoint(box.x + box.width, box.y + box.height),
		cvScalar(0xff, 0x00, 0x00) /*����*/
	);
}
	


int main() {
	cvNamedWindow("Play Video", CV_WINDOW_AUTOSIZE); //�������� ���� ������ ����� �� �����
	CvCapture* capture = cvCreateFileCapture("D:\move1.AVI");
	//���������� ��������� �� ��������� ���� CvCapture. �������� ��� ���������� �� ����������
	IplImage* frame;

     frame= cvQueryFrame(capture);
		
	 cvShowImage("Play Video", frame); //����������� 
	 //cvWaitKey(0);


	box = cvRect(-1, -1, 0, 0);

	IplImage* temp = cvCloneImage(frame);

	// ����������� ������� ��������� ������
	// � �������� �������� "param" ���������� �����������,
	// ������� ������� ��������� ������ ����� ������������
	//
	cvSetMouseCallback(
		"Play Video",
		mouse_callback,
		(void*)frame
	);
	// ����. ������� ���������� ����������� ������������� �����������
	// �� ��������� "temp" �����������, � ���� ������������ ������, �����
	// ������������� ���������� �� ��������� �����������, � ���������� ��������� ��������
	// ������������ �� ������.
	//
	while (1) {
		cvCopy(frame, temp);
		if (drawing_box) {
			draw_box(temp, box);
		}
		cvShowImage("Play Video", temp);
		if (box.height != 0 && box.width != 0) {
			IplImage* img = cvLoadImage("D:/img1.jpg");
			cvNamedWindow("Display Picture", CV_WINDOW_AUTOSIZE);
			cvShowImage("Display Picture", img);
			if (27 == cvWaitKey(0)) { 
			cvReleaseImage(&img);
			cvDestroyWindow("Display Picture");
			break; 
			}
		}

		cvWaitKey(0);
	}

	//correlation_tracker tracker;
	//tracker.start_track(frame, centered_rect(point(box.x+box.width/2,box.y+box.height/2 ), box.width, box.height));

	//���� ��������������� �����
	while (1) {
		frame = cvQueryFrame(capture);
		if (!frame) { break; }
		//tracker.update(frame);
		cvShowImage("Play Video", frame);
		//tracker.get_position();
		if (27 == cvWaitKey(30)) { break; }
	}
	
		}

// ������� ��������� ������. ���� ������������ ������ ����� �������
// ����, �������������� ������� ���������. ����� ������������ ���������
// ��� �������, ���������� ���������� �������������� �� ������� �����������.
// ��� ����������� ���� ���������� ��������� �������� ��������������
//
void mouse_callback(int event, int x, int y, int flags, void* param) {
	IplImage* frame = (IplImage*)param;
	switch (event) {
	case CV_EVENT_MOUSEMOVE: {
		if (drawing_box) {
			box.width = x - box.x;
			box.height = y - box.y;
		}
	}
							 break;
	case CV_EVENT_LBUTTONDOWN: {
		drawing_box = true;
		box = cvRect(x, y, 0, 0);
	}
							   break;
	case CV_EVENT_LBUTTONUP: {
		drawing_box = false;
		if (box.width<0) {
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height<0) {
			box.y += box.height;
			box.height *= -1;
		}
		draw_box(frame, box);
	}
							 break;
	}
}