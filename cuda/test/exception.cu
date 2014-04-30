
#include "../exception.hpp"
#include <iostream>

namespace U = cujak::util;

void test_exception(cudaError_t err) {
  try {
    CUDA_EXEC(err);
  }
  catch (U::CUDA_ERROR &e) {
    std::cout << "Error type: " << e.err << '\n' << "Error occured at "
              << e.filename << ":" << e.line << ":" << e.funcname << '\n'
              << e.what() << '\n' << std::endl;
  }
}

void test_exception(cufftResult err) {
  try {
    CUFFT_EXEC(err);
  }
  catch (U::CUFFT_ERROR &e) {
    std::cout << "Error type: " << e.err << '\n' << "Error occured at "
              << e.filename << ":" << e.line << ":" << e.funcname << '\n'
              << e.what() << '\n' << std::endl;
  }
}


int main(int argc, char const *argv[]) {
  test_exception(cudaSuccess);
  test_exception(cudaErrorMissingConfiguration);
  test_exception(cudaErrorMemoryAllocation);
  test_exception(cudaErrorInitializationError);
  test_exception(cudaErrorLaunchFailure);
  test_exception(cudaErrorPriorLaunchFailure);
  test_exception(cudaErrorLaunchTimeout);
  test_exception(cudaErrorLaunchOutOfResources);
  test_exception(cudaErrorInvalidDeviceFunction);
  test_exception(cudaErrorInvalidConfiguration);
  test_exception(cudaErrorInvalidDevice);
  test_exception(cudaErrorInvalidValue);
  test_exception(cudaErrorInvalidPitchValue);
  test_exception(cudaErrorInvalidSymbol);
  test_exception(cudaErrorMapBufferObjectFailed);
  test_exception(cudaErrorUnmapBufferObjectFailed);
  test_exception(cudaErrorInvalidHostPointer);
  test_exception(cudaErrorInvalidDevicePointer);
  test_exception(cudaErrorInvalidTexture);
  test_exception(cudaErrorInvalidTextureBinding);
  test_exception(cudaErrorInvalidChannelDescriptor);
  test_exception(cudaErrorInvalidMemcpyDirection);
  test_exception(cudaErrorAddressOfConstant);
  test_exception(cudaErrorTextureFetchFailed);
  test_exception(cudaErrorTextureNotBound);
  test_exception(cudaErrorSynchronizationError);
  test_exception(cudaErrorInvalidFilterSetting);
  test_exception(cudaErrorInvalidNormSetting);
  test_exception(cudaErrorMixedDeviceExecution);
  test_exception(cudaErrorCudartUnloading);
  test_exception(cudaErrorUnknown);
  test_exception(cudaErrorNotYetImplemented);
  test_exception(cudaErrorMemoryValueTooLarge);
  test_exception(cudaErrorInvalidResourceHandle);
  test_exception(cudaErrorNotReady);
  test_exception(cudaErrorInsufficientDriver);
  test_exception(cudaErrorSetOnActiveProcess);
  test_exception(cudaErrorInvalidSurface);
  test_exception(cudaErrorNoDevice);
  test_exception(cudaErrorECCUncorrectable);
  test_exception(cudaErrorSharedObjectSymbolNotFound);
  test_exception(cudaErrorSharedObjectInitFailed);
  test_exception(cudaErrorUnsupportedLimit);
  test_exception(cudaErrorDuplicateVariableName);
  test_exception(cudaErrorDuplicateTextureName);
  test_exception(cudaErrorDuplicateSurfaceName);
  test_exception(cudaErrorDevicesUnavailable);
  test_exception(cudaErrorInvalidKernelImage);
  test_exception(cudaErrorNoKernelImageForDevice);
  test_exception(cudaErrorIncompatibleDriverContext);
  test_exception(cudaErrorPeerAccessAlreadyEnabled);
  test_exception(cudaErrorPeerAccessNotEnabled);
  test_exception(cudaErrorDeviceAlreadyInUse);
  test_exception(cudaErrorProfilerDisabled);
  test_exception(cudaErrorProfilerNotInitialized);
  test_exception(cudaErrorProfilerAlreadyStarted);
  test_exception(cudaErrorProfilerAlreadyStopped);
  test_exception(cudaErrorAssert);
  test_exception(cudaErrorTooManyPeers);
  test_exception(cudaErrorHostMemoryAlreadyRegistered);
  test_exception(cudaErrorHostMemoryNotRegistered);
  test_exception(cudaErrorOperatingSystem);
  test_exception(cudaErrorPeerAccessUnsupported);
  test_exception(cudaErrorLaunchMaxDepthExceeded);
  test_exception(cudaErrorLaunchFileScopedTex);
  test_exception(cudaErrorLaunchFileScopedSurf);
  test_exception(cudaErrorSyncDepthExceeded);
  test_exception(cudaErrorLaunchPendingCountExceeded);
  test_exception(cudaErrorNotPermitted);
  test_exception(cudaErrorNotSupported);
  test_exception(cudaErrorHardwareStackError);
  test_exception(cudaErrorIllegalInstruction);
  test_exception(cudaErrorMisalignedAddress);
  test_exception(cudaErrorInvalidAddressSpace);
  test_exception(cudaErrorInvalidPc);
  test_exception(cudaErrorIllegalAddress);
  test_exception(cudaErrorStartupFailure);
  test_exception(cudaErrorApiFailureBase);

  test_exception(CUFFT_SUCCESS);
  test_exception(CUFFT_INVALID_PLAN);
  test_exception(CUFFT_ALLOC_FAILED);
  test_exception(CUFFT_INVALID_TYPE);
  test_exception(CUFFT_INVALID_VALUE);
  test_exception(CUFFT_INTERNAL_ERROR);
  test_exception(CUFFT_EXEC_FAILED);
  test_exception(CUFFT_SETUP_FAILED);
  test_exception(CUFFT_INVALID_SIZE);
  test_exception(CUFFT_UNALIGNED_DATA);
  test_exception(CUFFT_INCOMPLETE_PARAMETER_LIST);
  test_exception(CUFFT_INVALID_DEVICE);
  test_exception(CUFFT_PARSE_ERROR);
  test_exception(CUFFT_NO_WORKSPACE);
  return 0;
}
