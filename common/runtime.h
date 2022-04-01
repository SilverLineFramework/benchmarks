/**
 * @file runtime.h
 * @brief Main loop
 */

#ifndef RUNTIME_H
#define RUNTIME_H

#if !defined(PROFILE_ACTIVE) && !defined(PROFILE_PASSIVE)
#define PROFILE_ACTIVE
#endif

#ifdef PROFILE_ACTIVE
#include "active.h"
#endif

#ifdef PROFILE_PASSIVE
#include "passive.h"
#endif

#endif
