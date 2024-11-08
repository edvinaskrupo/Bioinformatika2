// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2010, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================

#ifndef SEQAN_HEADER_BASIC_DEBUG_H
#define SEQAN_HEADER_BASIC_DEBUG_H

#ifndef SEQAN_DEBUG_OR_TEST_
#ifdef SEQAN_DEBUG
#define SEQAN_DEBUG_OR_TEST_
#else //#ifdef SEQAN_DEBUG
#ifdef SEQAN_TEST
#define SEQAN_DEBUG_OR_TEST_
#endif //#ifdef SEQAN_TEST
#endif //#ifdef SEQAN_DEBUG
#endif //#ifndef SEQAN_DEBUG_OR_TEST_


#ifdef SEQAN_DEBUG_OR_TEST_
#include <cstdio>
#endif //#ifdef SEQAN_DEBUG_OR_TEST_

#ifdef SEQAN_DEBUG

//throw a fatal debug report if _cond is false
#define SEQAN_ASSERT(_cond) { if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Error< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, #_cond " is FALSE"); }
#define SEQAN_ASSERT1(_cond) SEQAN_ASSERT(_cond)
#define SEQAN_ASSERT2(_cond, _comment) { if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Error< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, _comment); }

//throw a debug report if _cond is false
#define SEQAN_CHECK(_cond) { if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Message< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, #_cond " is FALSE"); }
#define SEQAN_CHECK1(_cond) SEQAN_CHECK(_cond)
#define SEQAN_CHECK2(_cond, _comment) { if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Message< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, _comment); }

#define SEQAN_DO(_cond) { if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Message< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, #_cond " is FALSE"); }
#define SEQAN_DO1(_cond) SEQAN_DO(_cond)
#define SEQAN_DO2(_cond, _comment) { if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Error< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, _comment); }

//report a message
#define SEQAN_ABORT(_comment) { ::SEQAN_NAMESPACE_MAIN::debug::Error< ::SEQAN_NAMESPACE_MAIN::debug::Report >(__FILE__, __LINE__, _comment); }
#define SEQAN_REPORT(_comment) { ::SEQAN_NAMESPACE_MAIN::debug::Message< ::SEQAN_NAMESPACE_MAIN::debug::Report >(__FILE__, __LINE__, _comment); }

#else //#ifdef SEQAN_DEBUG

//disable debug reports in release built
#define SEQAN_ASSERT(_cond) {}
#define SEQAN_ASSERT1(_cond) {}
#define SEQAN_ASSERT2(_cond, _comment) {}

#define SEQAN_CHECK(_cond) {}
#define SEQAN_CHECK1(_cond) {}
#define SEQAN_CHECK2(_cond, _comment) {}

#define SEQAN_DO(_cond) { if (_cond) {} }
#define SEQAN_DO1(_cond) SEQAN_DO(_cond)
#define SEQAN_DO2(_cond, _comment) { _cond; }

#define SEQAN_ABORT(_comment) {}
#define SEQAN_REPORT(_comment) {}

#endif //#ifdef SEQAN_DEBUG

#ifdef SEQAN_TEST

//test a condition and report test result
#define SEQAN_TASSERT(_cond) \
	{ if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Error< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, "(" #_cond ") is FALSE"); }
#define SEQAN_TASSERT1(_cond) SEQAN_TASSERT(_cond)
#define SEQAN_TASSERT2(_cond, _comment) \
	{ if (!(_cond)) ::SEQAN_NAMESPACE_MAIN::debug::Error< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, _comment); }

#define SEQAN_TCHECK(_cond) \
	{ if (_cond) ::SEQAN_NAMESPACE_MAIN::debug::Result< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, "(" #_cond ") is TRUE"); \
	else ::SEQAN_NAMESPACE_MAIN::debug::Result< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, "(" #_cond ") is FALSE"); }
#define SEQAN_TCHECK1(_cond) SEQAN_TCHECK(_cond)
#define SEQAN_TCHECK2(_cond, _comment) \
	{ if (_cond) ::SEQAN_NAMESPACE_MAIN::debug::Result< ::SEQAN_NAMESPACE_MAIN::debug::Check >(__FILE__, __LINE__, _comment); }

//report a test result
#define SEQAN_TABORT(_comment) { ::SEQAN_NAMESPACE_MAIN::debug::Error< ::SEQAN_NAMESPACE_MAIN::debug::Report >(__FILE__, __LINE__, _comment); }
#define SEQAN_TREPORT(_comment) { ::SEQAN_NAMESPACE_MAIN::debug::Result< ::SEQAN_NAMESPACE_MAIN::debug::Report >(__FILE__, __LINE__, _comment); }

#else //#ifdef SEQAN_TEST

#define SEQAN_TASSERT(_cond) {}
#define SEQAN_TASSERT1(_cond) {}
#define SEQAN_TASSERT2(_cond, _comment) {}

#define SEQAN_TCHECK(_cond) {}
#define SEQAN_TABORT(_comment) {}
#define SEQAN_TREPORT(_comment) {}

#endif //#ifdef SEQAN_TEST
//____________________________________________________________________________

#ifdef SEQAN_DEBUG_OR_TEST_

//Test Helper Functions

// compare two files, do not translate linebreaks
inline bool 
_compareBinaryFiles(const char * file1, const char * file2)
{
	bool ret = false;

	FILE * fl1 = fopen(file1, "rb");
	if (!fl1) return ret;

	FILE * fl2 = fopen(file2, "rb");
	if (!fl2)
	{
		fclose(fl1);
		return ret;
	}

	while (!feof(fl1) && !feof(fl2))
	{
		if (fgetc(fl1) != fgetc(fl2)) goto End;
	}

	ret = feof(fl1) && feof(fl2);

End:
	fclose(fl2);
	fclose(fl1);

	return ret;

}
//____________________________________________________________________________

//one line break is either \r, \n, or \r\n.
//a single line break is skipped.
//the second line break is transformed into \n
inline void 
_compareTextFilesReadChar(FILE * fl, char & c, int & num_lb, bool & is_eof)
{
	num_lb = 0;
	is_eof = false;

	c = fgetc(fl);
	while ((c == '\r') || (c == '\n'))
	{
		++num_lb;
		if (c == '\r')
		{
			c = fgetc(fl);
			if (feof(fl)) is_eof = true;
			else
			{
				if (c == '\n')
				{
					c = fgetc(fl);
					if (feof(fl)) is_eof = true;
				}
			}
		}
		else if (c == '\n')
		{
			c = fgetc(fl);
			if (feof(fl)) is_eof = true;
		}
	}
}

// compare two files, translate linebreaks
inline bool 
_compareTextFiles(const char * file1, const char * file2)
{
	FILE * fl1 = fopen(file1, "rb");
	if (!fl1) return false;

	FILE * fl2 = fopen(file2, "rb");
	if (!fl2)
	{
		fclose(fl1);
		return false;
	}

	bool ret = false;

	int num_lb1, num_lb2;
	bool is_eof1, is_eof2;
	char c1, c2;

	while (!feof(fl1) && !feof(fl2))
	{
		_compareTextFilesReadChar(fl1, c1, num_lb1, is_eof1);
		_compareTextFilesReadChar(fl2, c2, num_lb2, is_eof2);

		if (num_lb1 != num_lb2)
		{
			goto End;
		}
		if (is_eof1 ^ is_eof2)
		{
			goto End;
		}
		if (c1 != c2)
		{
			goto End;
		}
	}

	ret = feof(fl1) && feof(fl2);

End:
	fclose(fl2);
	fclose(fl1);

	return ret;

}


//____________________________________________________________________________

namespace SEQAN_NAMESPACE_MAIN
{

namespace debug
{

//action of SEQAN_ASSERT, SEQAN_TCHECK and SEQAN_CHECK
//use as template argument for Error<> and Message<> and Result<>
class Check {};

//action of SEQAN_ABORT, SEQAN_TREPORT and SEQAN_REPORT
//use as template argument for Error<> and Message<> and Result<>
class Report {};


//report fatal error
//template argument TAction is the action (Check or Report)
//use explicit instatiation for overwriting the default behavior
template <typename TAction>
void Error(const char * file, int line, const char * comment)
{
	std::fprintf(stderr, "%s(%i) : SEQAN: %s\nSEQAN: execution aborted\n", file, line, comment);
	exit(1);
}

template <typename TAction>
void Error(const char * file, int line)
{
  Error<TAction>(file, line, "-");
}

//report debug message
//template argument TAction is the action (Check or Report)
//use explicit instatiation for overwriting the default behavior
template <typename TAction>
void Message(const char * file, int line, const char * comment)
{
	std::fprintf(stderr, "%s(%i) : SEQAN: %s\n", file, line, comment);
}

template <typename TAction>
void Message(const char * file, int line)
{
  Message<TAction>(file, line, "-");
}

//report test result
//template argument TAction is the action (Check or Report)
//use explicit instatiation for overwriting the default behavior
template <typename TAction>
void Result(const char * file, int line, const char * comment)
{
	std::fprintf(stdout, "%s(%i) : %s\n", file, line, comment);
}

template <typename TAction>
void Result(const char * file, int line)
{
  Result<TAction>(file, line, "-");
}

} //namespace debug

} //namespace SEQAN_NAMESPACE_MAIN

#endif //#ifdef SEQAN_DEBUG_OR_TEST_


//____________________________________________________________________________
//Checkpoint Testing

//note: this framework relies on the filenames in the project to be unique 

#ifdef SEQAN_TEST

#include <set>
#include <vector>
#include <cstring>

namespace SEQAN_NAMESPACE_MAIN
{
namespace debug
{
struct Checkpoint
{
	char const* file;
	unsigned int line;
};

struct CheckpointLess : public ::std::binary_function <Checkpoint, Checkpoint, bool>
{
	inline bool operator() (Checkpoint const &a, Checkpoint const &b) const
	{
		int c = strcmp(a.file, b.file);
		return c < 0 || (c == 0 && a.line < b.line);
	}
};

template <typename T = void>
struct CheckpointStore
{
	static ::std::set<Checkpoint, CheckpointLess> data;
};
template <typename T>
::std::set<Checkpoint, CheckpointLess> CheckpointStore<T>::data;


inline bool 
checkpoint(unsigned int line, char const* file)
{
	char const* file_name = strrchr(file, '/');
	char const* file_name_2 = strrchr(file, '\\');
	if (file_name_2 > file_name) file_name = file_name_2;
	if (!file_name) file_name = file;
	else ++file_name;

	Checkpoint cp = {file_name, line};
	CheckpointStore<>::data.insert(cp);
	return true;
}
//#define SEQAN_CHECKPOINT ::SEQAN_NAMESPACE_MAIN::debug::checkpoint(__LINE__, __FILE__);


inline void 
testCheckpoint(char const* file, unsigned int line)
{
	Checkpoint cp = {file, line};
	if (CheckpointStore<>::data.find(cp) == CheckpointStore<>::data.end())
		Message< Report >(file, line, "Checkpoint lost");
}

inline void 
verifyCheckpoints(char const* file)
{
	char const* file_name = strrchr(file, '/');
	char const* file_name_2 = strrchr(file, '\\');
	if (file_name_2 > file_name) file_name = file_name_2;
	if (!file_name) file_name = file;
	else ++file_name;

        int len = strlen(::seqan::ClassTest::StaticData::pathToProjects()) +
            strlen("/") + strlen(file) + 1;
        char *absolutePath = new char[len];
        absolutePath[0] = '\0';
        strcat(absolutePath, ::seqan::ClassTest::StaticData::pathToProjects());
        strcat(absolutePath, "/");
        strcat(absolutePath, file);

	FILE * fl = ::std::fopen(absolutePath, "r");
        delete[] absolutePath;
	if (!fl)
	{
		Error< Report >(file, 0, "verifyCheckpoints could not find this file.");	
	}
	unsigned int line_number = 1;
	char buf[1<<16];

	while (::std::fgets(buf, sizeof(buf), fl))
	{
		if (::std::strstr(buf, "SEQAN_CHECKPOINT"))
		{
			testCheckpoint(file_name, line_number);
		}
		++line_number;
	}

	::std::fclose(fl);
}

} //namespace debug

} //namespace SEQAN_NAMESPACE_MAIN

#else //#ifdef SEQAN_TEST

//#define SEQAN_CHECKPOINT

#endif //#ifdef SEQAN_TEST

//____________________________________________________________________________

#endif //#ifndef SEQAN_HEADER_...
