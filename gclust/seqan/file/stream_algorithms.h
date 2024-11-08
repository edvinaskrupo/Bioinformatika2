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

#ifndef SEQAN_HEADER_STREAM_ALGORITHMS_H
#define SEQAN_HEADER_STREAM_ALGORITHMS_H


namespace SEQAN_NAMESPACE_MAIN
{
//////////////////////////////////////////////////////////////////////////////


/**
.Internal._streamPutInt:
..summary:Converts an integer to a character and writes it to stream.
..cat:Streams
..signature:_streamPutInt(stream, number [, format_string])
..param.target:An output stream.
...type:Adaption."std::iostream"
..param.number:A number that is written to $stream$.
*/
template <typename TStream>
inline void
_streamPutInt(TStream & target,
			  int number, 
			  char const * format_string)
{
SEQAN_CHECKPOINT
	char str[BitsPerValue<int>::VALUE];
	sprintf(str, format_string, number);
	_streamWrite(target, str);
}
template <typename TStream>
inline void
_streamPutInt(TStream & target,
			  int number)
{
SEQAN_CHECKPOINT
	_streamPutInt(target, number, "%d");
}

/**
.Internal._streamPutFloat:
..summary:Converts a float to a character and writes it to stream.
..cat:Streams
..signature:_streamPutFloat(stream, number [, format_string])
..param.target:An output stream.
...type:Adaption."std::iostream"
..param.number:A number that is written to $stream$.
*/
template <typename TStream>
inline void
_streamPutFloat(TStream & target,
			  double number, 
			  char const * format_string)
{
    SEQAN_CHECKPOINT;
	char str[BitsPerValue<float>::VALUE];
	sprintf(str, format_string, number);
	_streamWrite(target, str);
}
template <typename TStream>
inline void
_streamPutFloat(TStream & target,
				double number)
{
    SEQAN_CHECKPOINT;
	_streamPutFloat(target, number, "%f");
}


//////////////////////////////////////////////////////////////////////////////

template <typename TTarget, typename T1, typename T2, typename TCompression>
inline void
_streamWrite(TTarget & target,
			 Pair<T1, T2, TCompression> const & source)
{
SEQAN_CHECKPOINT
	_streamWrite(target, getValueI1(source));
	_streamWrite(target, getValueI2(source));
}

template <typename TTarget, typename T1, typename T2, typename T3, typename TCompression>
inline void
_streamWrite(TTarget & target,
			 Triple<T1, T2, T3, TCompression> const & source)
{
SEQAN_CHECKPOINT
	_streamWrite(target, getValueI1(source));
	_streamWrite(target, getValueI2(source));
	_streamWrite(target, getValueI3(source));
}

//////////////////////////////////////////////////////////////////////////////



/**
.Internal._streamWrite:
..summary:Writes a sequence to stream.
..cat:Streams
..signature:_streamWrite(stream, sequence)
..param.stream:An input stream.
..param.sequence:A sequence that is written to $stream$.
*/

template <typename TTarget, typename TSource>
inline void
_streamWrite(TTarget & target,
			 TSource const & source)
{
SEQAN_CHECKPOINT
	_streamWriteSeq(target, source, typename IsSequence<TSource const>::Type());
}

//____________________________________________________________________________

template <typename TTarget, typename TSource>
inline void
_streamWriteSeq(TTarget & target,
				TSource const & source,
				False const)
{
	_streamPut(target, source);
}

//____________________________________________________________________________

template <typename TTarget, typename TSource>
inline void
_streamWriteSeq(TTarget & target,
				TSource const & source,
				True const)
{
SEQAN_CHECKPOINT
	typename Iterator<TSource const, Standard>::Type it = begin(source, Standard());
	typename Iterator<TSource const, Standard>::Type it_end = end(source, Standard());

	for (; it != it_end; ++it)
	{
		typename GetValue<TSource const>::Type val_ = getValue(it);
		_streamWrite(target, val_);
	}
}

template <typename TTarget, typename TSourceValue>
inline void
_streamWriteSeq(TTarget & target,
			    TSourceValue const * source,
				True const)
{
SEQAN_CHECKPOINT

	for (; !atEnd(source); ++source)
	{
		_streamWrite(target, *source);
	}
}

//////////////////////////////////////////////////////////////////////////////

/**
.Internal._streamWriteRange:
..summary:Writes a range to stream.
..cat:Streams
..signature:_streamWriteRange(stream, begin_iterator, end_iterator)
..param.stream:An input stream.
..param.sequence:A sequence that is written to $stream$.
*/

template <typename TTarget, typename TIterator>
inline void
_streamWriteRange(TTarget & target,
				  TIterator begin_,
				  TIterator end_)
{
SEQAN_CHECKPOINT
	for (; begin_ != end_; ++begin_)
	{
		_streamPut(target, *begin_);
	}
}


	

//////////////////////////////////////////////////////////////////////////////

} //namespace SEQAN_NAMESPACE_MAIN

#endif //#ifndef SEQAN_HEADER_...
