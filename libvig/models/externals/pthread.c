#include <sched.h>
#include <pthread.h>

#ifdef KLEE_VERIFICATION
#  include <klee/klee.h>
#endif

pthread_t pthread_self(void) {
  // We are on CPU 0 - always
  return 0;
}

int pthread_getaffinity_np(pthread_t thread, size_t cpusetsize,
                           cpu_set_t *cpuset) {
#ifdef KLEE_VERIFICATION
  // We're running in a symbolic executor. the concept of "affinity" is
  // meaningless
  int ret = klee_int("pthread_getaffinity_np_return");
#else
  // We're not verifying here, pretend that the function succeeded
  int ret = 0;
#endif

  // However, we might be given uninitialized memory, so we need to set it
  if (ret >= 0) {
    // TODO all bits should be symbols...
    CPU_ZERO(cpuset);
    CPU_SET(0, cpuset);
  }

  return ret;
}

int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize,
                           const cpu_set_t *cpuset) {
  // Same remark as getaffinity
#ifdef KLEE_VERIFICATION
  int ret = klee_int("pthread_getaffinity_np_return");
#else
  int ret = 0;
#endif
  return ret;
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg) {
  // "On success, pthread_create() returns 0; on error, it returns an error
  // number, and the contents of *thread are undefined."
  // -- http://man7.org/linux/man-pages/man3/pthread_create.3.html
  return 0;
}

int pthread_setname_np(pthread_t thread, const char *name) {
  // just ignore it - we don't support getname anyway

  // "On success, these functions return 0; on error, they return a nonzero
  // error number."
  // -- http://man7.org/linux/man-pages/man3/pthread_setname_np.3.html
  return 0;
}
