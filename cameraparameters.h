#pragma once
/*****************************
00002 Copyright 2011 Rafael Muñoz Salinas. All rights reserved.
00003
00004 Redistribution and use in source and binary forms, with or without modification, are
00005 permitted provided that the following conditions are met:
00006
00007    1. Redistributions of source code must retain the above copyright notice, this list of
00008       conditions and the following disclaimer.
00009
00010    2. Redistributions in binary form must reproduce the above copyright notice, this list
00011       of conditions and the following disclaimer in the documentation and/or other materials
00012       provided with the distribution.
00013
00014 THIS SOFTWARE IS PROVIDED BY Rafael Muñoz Salinas ''AS IS'' AND ANY EXPRESS OR IMPLIED
00015 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
00016 FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rafael Muñoz Salinas OR
00017 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
00018 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
00019 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
00020 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
00021 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
00022 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
00023
00024 The views and conclusions contained in the software and documentation are those of the
00025 authors and should not be interpreted as representing official policies, either expressed
00026 or implied, of Rafael Muñoz Salinas.
00027 ********************************/
#ifndef _Aruco_CameraParameters_H
#define  _Aruco_CameraParameters_H
//#include <aruco/exports.h>
#include <exports.h>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
 namespace aruco
 {
	class ARUCO_EXPORTS  CameraParameters
		 {
		 public:
			
			     // 3x3 matrix (fx 0 cx, 0 fy cy, 0 0 1)
			     cv::Mat  CameraMatrix;
			 //4x1 matrix (k1,k2,p1,p2)
			     cv::Mat  Distorsion;
			 //size of the image
			     cv::Size CamSize;
			
			 CameraParameters();
			 CameraParameters(cv::Mat cameraMatrix, cv::Mat distorsionCoeff, cv::Size size) throw(cv::Exception);
			 void setParams(cv::Mat cameraMatrix, cv::Mat distorsionCoeff, cv::Size size) throw(cv::Exception);
			 CameraParameters(const CameraParameters &CI);
			
			     bool isValid()const {
			         return CameraMatrix.rows != 0 && CameraMatrix.cols != 0 && Distorsion.rows != 0 && Distorsion.cols != 0 && CamSize.width != -1 && CamSize.height != -1;
			
			}
			 CameraParameters & operator=(const CameraParameters &CI);
			 void readFromFile(string path)throw(cv::Exception);
			 void saveToFile(string path, bool inXML = true)throw(cv::Exception);
			
			     void readFromXMLFile(string filePath)throw(cv::Exception);
			
			     void resize(cv::Size size)throw(cv::Exception);
			
			     static cv::Point3f getCameraLocation(cv::Mat Rvec, cv::Mat Tvec);
			
			     void glGetProjectionMatrix(cv::Size orgImgSize, cv::Size size, double proj_matrix[16], double gnear, double gfar, bool invert = false)throw(cv::Exception);
			
			     void OgreGetProjectionMatrix(cv::Size orgImgSize, cv::Size size, double proj_matrix[16], double gnear, double gfar, bool invert = false)throw(cv::Exception);
			
			
			 private:
					 //GL routines
					
					     static void argConvGLcpara2(double cparam[3][4], int width, int height, double gnear, double gfar, double m[16], bool invert)throw(cv::Exception);
					 static int  arParamDecompMat(double source[3][4], double cpara[3][4], double trans[3][4])throw(cv::Exception);
					 static double norm(double a, double b, double c);
					 static double dot(double a1, double a2, double a3,
					                         double b1, double b2, double b3);
					
					
					 };
	
	 }
#endif

