/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_OPERATING_SYSTEM_MACROS_H
#define HEADER_GUARD_OPERATING_SYSTEM_MACROS_H

/*!
 * \brief Defines macros to help with operating system detection.
 * Use `#if` not `#ifdef` for these!
 *
 * Using `#ifdef` on these is useless, instead use `#if`.  This is
 * because they are always defined.  These work in normal if
 * statements as well.
 *
 * Example:
 *
 * \code
 #include <iostream>
 #include "operating_system_macros.hh"
 int main() {
    std::cout << (IS_OS_LINUX ? "Compiled on linux.\n"
                              : "Not compild on linux.\n");
 }
 * \endcode
 *
 * If it makes sense, prefer using these macros as variables rather
 * than with preprocessor `#if` statements as it will allow for
 * compile time checks that ensure your code still works on other
 * operating systems.
 */

/*!
 * \def IS_OS_LINUX
 * \brief Defined to `true` if compiled on linux, else `false`.
 */
/*!
 * \def IS_OS_MAC
 * \brief Defined to `true` if compiled on macintosh OSX, else
 * `false`.
 */
/*!
 * \def IS_OS_WIN
 * \brief Defined to `true` if compiled on a windows computer, else
 * `false`.
 */
/*!
 * \def IS_ARCH_64
 * \brief Defined to `true` if compiled on a 64 bit computer, else
 * `false`.
 */
/*!
 * \def IS_ARCH_32
 * \brief Defined to `false` if compiled on a 32 bit computer, else
 * `false`.
 */

#if defined(__linux__)
#  define IS_OS_LINUX true
#  define IS_OS_MAC false
#  define IS_OS_WIN false
#  if defined(__x86_64__)
#    define IS_ARCH_64 true
#    define IS_ARCH_32 false
#  else
#    define IS_ARCH_64 false
#    define IS_ARCH_32 true
#  endif
#elif defined(__APPLE__) && defined(__MACH__)
#  define IS_OS_LINUX false
#  define IS_OS_MAC true
#  define IS_OS_WIN false
#  if defined(__x86_64__)
#    define IS_ARCH_64 true
#    define IS_ARCH_32 false
#  else
#    define IS_ARCH_64 false
#    define IS_ARCH_32 true
#  endif
#elif defined(_WIN32)
#  define IS_OS_LINUX false
#  define IS_OS_MAC false
#  define IS_OS_WIN true
#  if defined(_WIN64)
#    define IS_ARCH_64 true
#    define IS_ARCH_32 false
#  else
#    define IS_ARCH_64 false
#    define IS_ARCH_32 true
#  endif
#else
#  error Your operating system is not currently supported.
#  warning Please fix this error by implementing your OS correctly, \
then making a pull request to the github repository: \
https://github.com/czipperz/vick
#endif

#endif
