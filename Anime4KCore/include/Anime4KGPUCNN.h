#pragma once

#include"Anime4K.h"
#include"CNNProcessor.h"
#include"filterprocessor.h"

#include<fstream>

#ifdef __APPLE__
#include<OpenCL/opencl.h>
#else
#include<CL/cl.h>
#endif // SPECIAL OS

namespace Anime4KCPP
{
    class DLL Anime4KGPUCNN;
}

class Anime4KCPP::Anime4KGPUCNN :public Anime4K
{
public:
    Anime4KGPUCNN(const Parameters& parameters = Parameters());
    virtual ~Anime4KGPUCNN() = default;
    virtual void process() override;
    static void initGPU(unsigned int platformID = 0, unsigned int deviceID = 0, const CNNType type = CNNType::Default);
    static void releaseGPU();
    static bool isInitializedGPU();
private:
    void runKernelACNet(cv::InputArray orgImg, cv::OutputArray dstImg);
    void runKernelACNetHDN(cv::InputArray orgImg, cv::OutputArray dstImg);
    static void initOpenCL(const CNNType type);
    static void releaseOpenCL();
    static std::string readKernel(const std::string& fileName);

    virtual ProcessorType getProcessorType() override;
private:
    static bool isInitialized;

    static cl_context context;
    static cl_command_queue commandQueue;
    static cl_program programACNet;
    static cl_program programACNetHDN;
    static cl_device_id device;

    static unsigned int pID;
    static unsigned int dID;

#ifdef BUILT_IN_KERNEL
    static const std::string ACNetKernelSourceString;
    static const std::string ACNetHDNKernelSourceString;
#endif // BUILT_IN_KERNEL

};
