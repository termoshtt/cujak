#pragma once

#include "driver_types.h"

#include <stdexcept>
#include <string>

namespace cujak {
namespace util {

struct CUDA_ERROR : public std::exception {
  cudaError_t err;
  std::string filename, funcname;
  int line;
  CUDA_ERROR(cudaError_t err, const char *filename, int line,
             const char *funcname)
      : err(err), filename(filename), funcname(funcname), line(line) {}
  virtual ~CUDA_ERROR() throw() {};
  const char *what() const throw();
};

inline void cuda_exec(cudaError_t err, const char *filename, int line,
                      const char *funcname) {
  if (err != cudaSuccess)
    throw CUDA_ERROR(err, filename, line, funcname);
}

#define CUDA_EXEC(err) cujak::util::cuda_exec(err, __FILE__, __LINE__, __func__)

inline const char *CUDA_ERROR::what() const throw() {
  switch (err) {
  case cudaSuccess:
    return "The API call returned with no errors. In the case of query calls, "
           "this can also mean that the operation being queried is complete "
           "(see cudaEventQuery() and cudaStreamQuery()).";
  case cudaErrorMissingConfiguration:
    return "The device function being invoked (usually via cudaLaunch()) was "
           "not previously configured via the cudaConfigureCall() function.";
  case cudaErrorMemoryAllocation:
    return "The API call failed because it was unable to allocate enough "
           "memory to perform the requested operation.";
  case cudaErrorInitializationError:
    return "The API call failed because the CUDA driver and runtime could not "
           "be initialized.";
  case cudaErrorLaunchFailure:
    return "An exception occurred on the device while executing a kernel. "
           "Common causes include dereferencing an invalid device pointer and "
           "accessing out of bounds shared memory. The device cannot be used "
           "until cudaThreadExit() is called. All existing device memory "
           "allocations are invalid and must be reconstructed if the program "
           "is to continue using CUDA.";
  case cudaErrorPriorLaunchFailure:
    return "Deprecated This error return is deprecated as of CUDA 3.1. Device "
           "emulation mode was removed with the CUDA 3.1 release.  This "
           "indicated that a previous kernel launch failed. This was "
           "previously used for device emulation of kernel launches.  ";
  case cudaErrorLaunchTimeout:
    return "This indicates that the device kernel took too long to execute. "
           "This can only occur if timeouts are enabled - see the device "
           "property kernelExecTimeoutEnabled for more information. The device "
           "cannot be used until cudaThreadExit() is called. All existing "
           "device memory allocations are invalid and must be reconstructed if "
           "the program is to continue using CUDA.";
  case cudaErrorLaunchOutOfResources:
    return "This indicates that a launch did not occur because it did not have "
           "appropriate resources. Although this error is similar to "
           "cudaErrorInvalidConfiguration, this error usually indicates that "
           "the user has attempted to pass too many arguments to the device "
           "kernel, or the kernel launch specifies too many threads for the "
           "kernel's register count.";
  case cudaErrorInvalidDeviceFunction:
    return "The requested device function does not exist or is not compiled "
           "for the proper device architecture.";
  case cudaErrorInvalidConfiguration:
    return "This indicates that a kernel launch is requesting resources that "
           "can never be satisfied by the current device. Requesting more "
           "shared memory per block than the device supports will trigger this "
           "error, as will requesting too many threads or blocks. See "
           "cudaDeviceProp for more device limitations.";
  case cudaErrorInvalidDevice:
    return "This indicates that the device ordinal supplied by the user does "
           "not correspond to a valid CUDA device.";
  case cudaErrorInvalidValue:
    return "This indicates that one or more of the parameters passed to the "
           "API call is not within an acceptable range of values.";
  case cudaErrorInvalidPitchValue:
    return "This indicates that one or more of the pitch-related parameters "
           "passed to the API call is not within the acceptable range for "
           "pitch.";
  case cudaErrorInvalidSymbol:
    return "This indicates that the symbol name/identifier passed to the API "
           "call is not a valid name or identifier.";
  case cudaErrorMapBufferObjectFailed:
    return "This indicates that the buffer object could not be mapped.";
  case cudaErrorUnmapBufferObjectFailed:
    return "This indicates that the buffer object could not be unmapped.";
  case cudaErrorInvalidHostPointer:
    return "This indicates that at least one host pointer passed to the API "
           "call is not a valid host pointer.";
  case cudaErrorInvalidDevicePointer:
    return "This indicates that at least one device pointer passed to the API "
           "call is not a valid device pointer.";
  case cudaErrorInvalidTexture:
    return "This indicates that the texture passed to the API call is not a "
           "valid texture.";
  case cudaErrorInvalidTextureBinding:
    return "This indicates that the texture binding is not valid. This occurs "
           "if you call cudaGetTextureAlignmentOffset() with an unbound "
           "texture.";
  case cudaErrorInvalidChannelDescriptor:
    return "This indicates that the channel descriptor passed to the API call "
           "is not valid. This occurs if the format is not one of the formats "
           "specified by cudaChannelFormatKind, or if one of the dimensions is "
           "invalid.";
  case cudaErrorInvalidMemcpyDirection:
    return "This indicates that the direction of the memcpy passed to the API "
           "call is not one of the types specified by cudaMemcpyKind.";
  case cudaErrorAddressOfConstant:
    return "Deprecated. This error return is deprecated as of CUDA 3.1. "
           "Variables in constant memory may now have their address taken by "
           "the runtime via cudaGetSymbolAddress().  This indicated that the "
           "user has taken the address of a constant variable, which was "
           "forbidden up until the CUDA 3.1 release.";
  case cudaErrorTextureFetchFailed:
    return "Deprecated. This error return is deprecated as of CUDA 3.1. Device "
           "emulation mode was removed with the CUDA 3.1 release.  This "
           "indicated that a texture fetch was not able to be performed. This "
           "was previously used for device emulation of texture operations.";
  case cudaErrorTextureNotBound:
    return "Deprecated. This error return is deprecated as of CUDA 3.1. Device "
           "emulation mode was removed with the CUDA 3.1 release.  This "
           "indicated that a texture was not bound for access. This was "
           "previously used for device emulation of texture operations.";
  case cudaErrorSynchronizationError:
    return "Deprecated.  This error return is deprecated as of CUDA 3.1. "
           "Device emulation mode was removed with the CUDA 3.1 release.  This "
           "indicated that a synchronization operation had failed. This was "
           "previously used for some device emulation functions.";
  case cudaErrorInvalidFilterSetting:
    return "This indicates that a non-float texture was being accessed with "
           "linear filtering. This is not supported by CUDA.";
  case cudaErrorInvalidNormSetting:
    return "This indicates that an attempt was made to read a non-float "
           "texture as a normalized float. This is not supported by CUDA.";
  case cudaErrorMixedDeviceExecution:
    return "Deprecated.  This error return is deprecated as of CUDA 3.1. "
           "Device emulation mode was removed with the CUDA 3.1 release.  "
           "Mixing of device and device emulation code was not allowed.";
  case cudaErrorCudartUnloading:
    return "This indicates that a CUDA Runtime API call cannot be executed "
           "because it is being called during process shut down, at a point in "
           "time after CUDA driver has been unloaded.";
  case cudaErrorUnknown:
    return "This indicates that an unknown internal error has occurred.";
  case cudaErrorNotYetImplemented:
    return "Deprecated. This error return is deprecated as of CUDA 4.1. This "
           "indicates that the API call is not yet implemented. Production "
           "releases of CUDA will never return this error.";
  case cudaErrorMemoryValueTooLarge:
    return "Deprecated.  This error return is deprecated as of CUDA 3.1. "
           "Device emulation mode was removed with the CUDA 3.1 release.  This "
           "indicated that an emulated device pointer exceeded the 32-bit "
           "address range.";
  case cudaErrorInvalidResourceHandle:
    return "This indicates that a resource handle passed to the API call was "
           "not valid. Resource handles are opaque types like cudaStream_t and "
           "cudaEvent_t.";
  case cudaErrorNotReady:
    return "This indicates that asynchronous operations issued previously have "
           "not completed yet. This result is not actually an error, but must "
           "be indicated differently than cudaSuccess (which indicates "
           "completion). Calls that may return this value include "
           "cudaEventQuery() and cudaStreamQuery().";
  case cudaErrorInsufficientDriver:
    return "This indicates that the installed NVIDIA CUDA driver is older than "
           "the CUDA runtime library. This is not a supported configuration. "
           "Users should install an updated NVIDIA display driver to allow the "
           "application to run.";
  case cudaErrorSetOnActiveProcess:
    return "This indicates that the user has called cudaSetValidDevices(), "
           "cudaSetDeviceFlags(), cudaD3D9SetDirect3DDevice(), "
           "cudaD3D10SetDirect3DDevice, cudaD3D11SetDirect3DDevice(), or "
           "cudaVDPAUSetVDPAUDevice() after initializing the CUDA runtime by "
           "calling non-device management operations (allocating memory and "
           "launching kernels are examples of non-device management "
           "operations). This error can also be returned if using "
           "runtime/driver interoperability and there is an existing CUcontext "
           "active on the host thread.";
  case cudaErrorInvalidSurface:
    return "This indicates that the surface passed to the API call is not a "
           "valid surface.";
  case cudaErrorNoDevice:
    return "This indicates that no CUDA-capable devices were detected by the "
           "installed CUDA driver.";
  case cudaErrorECCUncorrectable:
    return "This indicates that an uncorrectable ECC error was detected during "
           "execution.";
  case cudaErrorSharedObjectSymbolNotFound:
    return "This indicates that a link to a shared object failed to resolve.";
  case cudaErrorSharedObjectInitFailed:
    return "This indicates that initialization of a shared object failed.";
  case cudaErrorUnsupportedLimit:
    return "This indicates that the cudaLimit passed to the API call is not "
           "supported by the active device.";
  case cudaErrorDuplicateVariableName:
    return "This indicates that multiple global or constant variables (across "
           "separate CUDA source files in the application) share the same "
           "string name.";
  case cudaErrorDuplicateTextureName:
    return "This indicates that multiple textures (across separate CUDA source "
           "files in the application) share the same string name.";
  case cudaErrorDuplicateSurfaceName:
    return "This indicates that multiple surfaces (across separate CUDA source "
           "files in the application) share the same string name.";
  case cudaErrorDevicesUnavailable:
    return "This indicates that all CUDA devices are busy or unavailable at "
           "the current time. Devices are often busy/unavailable due to use of "
           "cudaComputeModeExclusive, cudaComputeModeProhibited or when long "
           "running CUDA kernels have filled up the GPU and are blocking new "
           "work from starting. They can also be unavailable due to memory "
           "constraints on a device that already has active CUDA work being "
           "performed.";
  case cudaErrorInvalidKernelImage:
    return "This indicates that the device kernel image is invalid.";
  case cudaErrorNoKernelImageForDevice:
    return "This indicates that there is no kernel image available that is "
           "suitable for the device. This can occur when a user specifies code "
           "generation options for a particular CUDA source file that do not "
           "include the corresponding device configuration.";
  case cudaErrorIncompatibleDriverContext:
    return "This indicates that the current context is not compatible with "
           "this the CUDA Runtime. This can only occur if you are using CUDA "
           "Runtime/Driver interoperability and have created an existing "
           "Driver context using the driver API. The Driver context may be "
           "incompatible either because the Driver context was created using "
           "an older version of the API, because the Runtime API call expects "
           "a primary driver context and the Driver context is not primary, or "
           "because the Driver context has been destroyed. Please see "
           "Interactions with the CUDA Driver API for more information.";
  case cudaErrorPeerAccessAlreadyEnabled:
    return "This error indicates that a call to cudaDeviceEnablePeerAccess() "
           "is trying to re-enable peer addressing on from a context which has "
           "already had peer addressing enabled.";
  case cudaErrorPeerAccessNotEnabled:
    return "This error indicates that cudaDeviceDisablePeerAccess() is trying "
           "to disable peer addressing which has not been enabled yet via "
           "cudaDeviceEnablePeerAccess().";
  case cudaErrorDeviceAlreadyInUse:
    return "This indicates that a call tried to access an exclusive-thread "
           "device that is already in use by a different thread.";
  case cudaErrorProfilerDisabled:
    return "This indicates profiler is not initialized for this run. This can "
           "happen when the application is running with external profiling "
           "tools like visual profiler.";
  case cudaErrorProfilerNotInitialized:
    return "Deprecated. This error return is deprecated as of CUDA 5.0. It is "
           "no longer an error to attempt to enable/disable the profiling via "
           "cudaProfilerStart or cudaProfilerStop without initialization.";
  case cudaErrorProfilerAlreadyStarted:
    return "Deprecated.  This error return is deprecated as of CUDA 5.0. It is "
           "no longer an error to call cudaProfilerStart() when profiling is "
           "already enabled.";
  case cudaErrorProfilerAlreadyStopped:
    return "Deprecated.  This error return is deprecated as of CUDA 5.0. It is "
           "no longer an error to call cudaProfilerStop() when profiling is "
           "already disabled.";
  case cudaErrorAssert:
    return "An assert triggered in device code during kernel execution. The "
           "device cannot be used again until cudaThreadExit() is called. All "
           "existing allocations are invalid and must be reconstructed if the "
           "program is to continue using CUDA.";
  case cudaErrorTooManyPeers:
    return "This error indicates that the hardware resources required to "
           "enable peer access have been exhausted for one or more of the "
           "devices passed to cudaEnablePeerAccess().";
  case cudaErrorHostMemoryAlreadyRegistered:
    return "This error indicates that the memory range passed to "
           "cudaHostRegister() has already been registered.";
  case cudaErrorHostMemoryNotRegistered:
    return "This error indicates that the pointer passed to "
           "cudaHostUnregister() does not correspond to any currently "
           "registered memory region.";
  case cudaErrorOperatingSystem:
    return "This error indicates that an OS call failed.";
  case cudaErrorPeerAccessUnsupported:
    return "This error indicates that P2P access is not supported across the "
           "given devices.";
  case cudaErrorLaunchMaxDepthExceeded:
    return "This error indicates that a device runtime grid launch did not "
           "occur because the depth of the child grid would exceed the maximum "
           "supported number of nested grid launches.";
  case cudaErrorLaunchFileScopedTex:
    return "This error indicates that a grid launch did not occur because the "
           "kernel uses file-scoped textures which are unsupported by the "
           "device runtime. Kernels launched via the device runtime only "
           "support textures created with the Texture Object API's.";
  case cudaErrorLaunchFileScopedSurf:
    return "This error indicates that a grid launch did not occur because the "
           "kernel uses file-scoped surfaces which are unsupported by the "
           "device runtime. Kernels launched via the device runtime only "
           "support surfaces created with the Surface Object API's.";
  case cudaErrorSyncDepthExceeded:
    return "This error indicates that a call to cudaDeviceSynchronize made "
           "from the device runtime failed because the call was made at grid "
           "depth greater than than either the default (2 levels of grids) or "
           "user specified device limit cudaLimitDevRuntimeSyncDepth. To be "
           "able to synchronize on launched grids at a greater depth "
           "successfully, the maximum nested depth at which "
           "cudaDeviceSynchronize will be called must be specified with the "
           "cudaLimitDevRuntimeSyncDepth limit to the cudaDeviceSetLimit api "
           "before the host-side launch of a kernel using the device runtime. "
           "Keep in mind that additional levels of sync depth require the "
           "runtime to reserve large amounts of device memory that cannot be "
           "used for user allocations.";
  case cudaErrorLaunchPendingCountExceeded:
    return "This error indicates that a device runtime grid launch failed "
           "because the launch would exceed the limit "
           "cudaLimitDevRuntimePendingLaunchCount. For this launch to proceed "
           "successfully, cudaDeviceSetLimit must be called to set the "
           "cudaLimitDevRuntimePendingLaunchCount to be higher than the upper "
           "bound of outstanding launches that can be issued to the device "
           "runtime. Keep in mind that raising the limit of pending device "
           "runtime launches will require the runtime to reserve device memory "
           "that cannot be used for user allocations.";
  case cudaErrorNotPermitted:
    return "This error indicates the attempted operation is not permitted.";
  case cudaErrorNotSupported:
    return "This error indicates the attempted operation is not supported on "
           "the current system or device.";
  case cudaErrorHardwareStackError:
    return "Device encountered an error in the call stack during kernel "
           "execution, possibly due to stack corruption or exceeding the stack "
           "size limit. The context cannot be used, so it must be destroyed "
           "(and a new one should be created). All existing device memory "
           "allocations from this context are invalid and must be "
           "reconstructed if the program is to continue using CUDA.";
  case cudaErrorIllegalInstruction:
    return "The device encountered an illegal instruction during kernel "
           "execution The context cannot be used, so it must be destroyed (and "
           "a new one should be created). All existing device memory "
           "allocations from this context are invalid and must be "
           "reconstructed if the program is to continue using CUDA.";
  case cudaErrorMisalignedAddress:
    return "The device encountered a load or store instruction on a memory "
           "address which is not aligned. The context cannot be used, so it "
           "must be destroyed (and a new one should be created). All existing "
           "device memory allocations from this context are invalid and must "
           "be reconstructed if the program is to continue using CUDA.";
  case cudaErrorInvalidAddressSpace:
    return "While executing a kernel, the device encountered an instruction "
           "which can only operate on memory locations in certain address "
           "spaces (global, shared, or local), but was supplied a memory "
           "address not belonging to an allowed address space. The context "
           "cannot be used, so it must be destroyed (and a new one should be "
           "created). All existing device memory allocations from this context "
           "are invalid and must be reconstructed if the program is to "
           "continue using CUDA.";
  case cudaErrorInvalidPc:
    return "The device encountered an invalid program counter. The context "
           "cannot be used, so it must be destroyed (and a new one should be "
           "created). All existing device memory allocations from this context "
           "are invalid and must be reconstructed if the program is to "
           "continue using CUDA.";
  case cudaErrorIllegalAddress:
    return "The device encountered a load or store instruction on an invalid "
           "memory address. The context cannot be used, so it must be "
           "destroyed (and a new one should be created). All existing device "
           "memory allocations from this context are invalid and must be "
           "reconstructed if the program is to continue using CUDA.";
  case cudaErrorStartupFailure:
    return "This indicates an internal startup failure in the CUDA runtime.";
  case cudaErrorApiFailureBase:
    return "Deprecated. This error return is deprecated as of CUDA 4.1. Any "
           "unhandled CUDA driver error is added to this value and returned "
           "via the runtime. Production releases of CUDA should not return "
           "such errors.";
  default:
    return "Unknown Error Code.";
  }
}

} // namespace util
} // namespace cujak
