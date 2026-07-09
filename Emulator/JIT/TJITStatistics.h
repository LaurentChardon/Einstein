// ==============================
// File:			JITStatistics.h
// Project:			Einstein
//
// Copyright 2003-2026 by Paul Guyot (pguyot@kallisys.net).
//                     and Matthias Melcher (m.melcher@robowerk.com)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// ==============================
// $Id$
// ==============================

#ifndef EINSTEIN_TJITSTATISTICS_H
#define EINSTEIN_TJITSTATISTICS_H

// vvv--- configure the macros below before compiling Einstein

// To enable some simple statistics on the JIT, define this macro to 1.
// This will slow down the JIT a bit, but will give you some insight into
// the instructions that the JIT executes.
// #define JIT_ENABLE_STATISTICS 1
#undef JIT_ENABLE_STATISTICS

// Write all statistics to files in this directory.
#define JIT_STATISTICS_PATH "/Users/matt/dev/Einstein/Statistics/"

// If defined, count how many times each instruction is executed.
// This will write an array of 2M uint64_t values to "exec_count.bin" in the statistics directory.
#define JIT_STATISTIC_EXEC_COUNT 1

// If defined, track the order of execution of instructions.
// This will write an array of 2M uint32_t values to "exec_order.bin".
#define JIT_STATISTIC_EXEC_ORDER 1

// ^^^--- end of compile time configuration

#ifdef JIT_ENABLE_STATISTICS
#define JIT_STATISTIC_EXEC_ORDER 1

#include <K/Defines/KDefinitions.h>
#include <stdio.h>

class TEmulator;
class TSymbolList;

// Number of words needed to count hits in ROM
constexpr size_t k8MBWords = (8 * 1024 * 1024) / 4;

class TJITStatistics
{
	TEmulator* mEmulator { nullptr };

public:
	/// Write all our findings.
	void write_all();

	/// Called for every JIT instruction that is executed.
	/// \param at index into hit counter array; out-of-bounds indices are safe
	void hit(KUInt32 at);

	/// Reference back to the emulator.
	/// \param inEmulator pointer to the emulator instance
	void
	SetEmulator(TEmulator* inEmulator)
	{
		mEmulator = inEmulator;
	}

#ifdef JIT_STATISTIC_EXEC_COUNT
	uint64_t mExecCount[k8MBWords] { 0 };
	void write_exec_count();
#endif

#ifdef JIT_STATISTIC_EXEC_ORDER
	uint32_t mExecOrder[k8MBWords] { 0 };
	uint32_t mExecOrderIndex { 1 };
	void write_exec_order();
#endif
};

extern TJITStatistics gJITStatistics;

#endif

#endif // EINSTEIN_TJITSTATISTICS_H
