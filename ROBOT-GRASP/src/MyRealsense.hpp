/************************************************************************/
/* namespace cv                                                         */
/************************************************************************/
#include "Opencv.hpp"
#include "FileOperation.hpp"

/************************************************************************/
/* namespace pxc                                                        */
/************************************************************************/
#include <pxcimage.h>
#include <pxcsession.h>
#include <pxcsensemanager.h>
#include <pxcprojection.h>


class MyRealsense: public FileOperation
{
public:
	/**
	*  @brief testRegistration: End-TO-End Test RANSAC+ICP
	*  @param Dir					save color/depth data
	*  @param width, height, fps    camera setting
	*/
	MyRealsense(std::string& Dir, int width, int height, float fps = 60);
	/**
	*  @brief dataAcquire: Acquire color or depth data
	*/
	int dataAcquire();
	/**
	*  @brief show: demo with realtime capture video stream
	*/
	int show();
	/**
	*  @brief testRegistration: End-TO-End Test RANSAC+ICP
	*  @param model_path   which model to load (.pcd file format)
	*/
	int testRegistration(const string model_path, double PointCloudScale);
	/**
	*  @brief PXCImage2Mat: Convert RealSense's PXCImage to Opencv's Mat
	*/
	cv::Mat PXCImage2Mat(PXCImage* pxc);
private:
	int captureDepthandSave();
	string getSavePath(const string dir, time_t slot, long framecnt);
	int outputPCD(const string filename, PointSet &pSet, vector<PXCPoint3DF32> &vertices);

private:
	//DataAcquire Setting
	std::string dir_;
	std::string depthDir_;
	std::string rgbDir_;
	//Realsense
	PXCSession *pxcsession_ = 0;
	PXCSenseManager *pxcsm_ = 0;
	PXCCapture::Device *pxcdev_ = 0;
	PXCProjection *projection_ = 0;
	PXCSizeI32 camera_;
	pxcF32 fps_;
};