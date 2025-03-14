.. _limitations:

Known Limitations
*****************

This page outlines the known limitations of oneTBB to help you better understand its capabilities. 

Debug TBB In The SYCL Program
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Limitation:** The application may crash when using the Debug version of oneTBB in a SYCL program compiled with Intel(R) oneAPI DPC++/C++ Compiler. This happens because both ``tbb`` (Release version) and ``tbb_debug`` (Debug version) libraries load simultaneously, causing conflicts.

**Solution:** Do one of the following:

* Link the application with the Release version ``tbb`` instead of ``tbb_debug``.
* Use the ``qtbb`` flag provided by the Intel(R) oneAPI DPC++/C++ Compiler.

Freestanding Compilation Mode
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Limitation:** oneTBB does not support the freestanding compilation mode. 

**Risk:** Compiling an application that utilizes oneTBB headers using the Intel(R) oneAPI DPC++/C++ Compiler may result in failure on Windows* OS if the ``/Qfreestanding`` compiler option is employed.

Static Assert
^^^^^^^^^^^^^

**Limitation:** A static assert causes the compilation failures in oneTBB headers if the following conditions are satisfied:
  
* Compilation is done with Clang 12.0.0 or a more recent version. 
* The LLVM standard library is employed, coupled with the use of the ``-ffreestanding`` flag and C++11/14 compiler options.

**Risk:** The compilation failures. 

Interface Incompatibilities: TBB vs oneTBB
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Limitation:** An application using Parallel STL algorithms in the ``libstdc++`` versions 9 and 10 may fail to compile due to incompatible interface changes between earlier versions of Threading Building Blocks (TBB) and oneAPI Threading Building Blocks (oneTBB). 

**Solution:** Disable support for Parallel STL algorithms by defining ``PSTL_USE_PARALLEL_POLICIES`` (in libstdc++ 9) or ``_GLIBCXX_USE_TBB_PAR_BACKEND`` (in libstdc++ 10) macro to zero before inclusion of the first standard header file in each translation unit.

Incorrect Installation Location
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Limitation:** On Linux* OS, if oneAPI Threading Building Blocks (oneTBB) or Threading Building Blocks (TBB) are installed in a system folder, such as ``/usr/lib64``, the application may fail to link due to the order in which the linker searches for libraries.  

**Risk:** The issue does not affect the program execution.

**Solution:** Use the ``-L`` linker option to specify the correct location of oneTBB library. 

``fork()`` Support 
^^^^^^^^^^^^^^^^^^^

**Limitation:** oneTBB does not support ``fork()``. 

**Solution:** To work-around the issue, consider using ``task_scheduler_handle`` to join oneTBB worker threads before using ``fork()``.

Dynamic Malloc Replacement and Topology API Incompatibilities
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

**Limitation:** On Linux* OS, using dynamic malloc replacement with ``tbb::info`` and ``tbb::task_arena::constraints`` APIs may result in runtime failures.

**Solution:** Set ``TBB_ENABLE_SANITIZERS=1`` in the environment. This informs that dynamic malloc replacement is used.
