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

#ifndef SEQAN_HEADER_BASIC_TRANSPORT_H
#define SEQAN_HEADER_BASIC_TRANSPORT_H

namespace SEQAN_NAMESPACE_MAIN
{

//////////////////////////////////////////////////////////////////////////////
//assign
//////////////////////////////////////////////////////////////////////////////

/**
.Function.assign:
..summary:Assigns one object to another object.
..cat:Content Manipulation
..signature:assign(target, source)
..signature:assign(target, source [, limit] [,resize_tag])
..param.target: Gets the content of $source$.
..param.source: Is copied to $target$.
..param.limit: The maximal length of $target$ after the operation. (optional)
...remarks:This arguments can be applied if $target$ is a container.
..param.resize_tag: Specifies the strategy that is applied if $target$ has not enough capacity to store the complete content. (optional)
...type:Tag.Overflow Strategy
...default:Specified by @Metafunction.DefaultOverflowImplicit@ of the $target$ type.
...remarks:This arguments can be applied if $target$ is a container.
..remarks:$assign(target, source)$ is semantically equivalent to $target = source$. 
..include:seqan/basic.h
*/

template <typename TTarget, typename TSource>
inline void
assign(TTarget & target,
	   TSource & source)
{
SEQAN_CHECKPOINT
	target = source;
}
template <typename TTarget, typename TSource>
inline void
assign(TTarget & target,
	   TSource const & source)
{
SEQAN_CHECKPOINT
	target = source;
}

//////////////////////////////////////////////////////////////////////////////

template <typename TSpec> struct Proxy;

template<typename TTargetSpec, typename TSource>
inline void 
assign(Proxy<TTargetSpec> & target,
	   TSource & source)
{
SEQAN_CHECKPOINT
	assignValue(iter(target), source);
}

template<typename TTargetSpec, typename TSource>
inline void 
assign(Proxy<TTargetSpec> & target,
	   TSource const & source)
{
SEQAN_CHECKPOINT
	assignValue(iter(target), source);
}

//////////////////////////////////////////////////////////////////////////////
// move
//////////////////////////////////////////////////////////////////////////////

/**
.Function.move:
..summary:Hands over content from one container to another container.
..cat:Content Manipulation
..signature:move(target, source)
..param.target:A container $source$ is moved to.
..param.source:A container that is moved to $target$.
..remarks:The function tries to hand over the contents of $source$ to $target$.
If this is possible, $source$ looses its content and will therefore be empty after this operation.
Otherwise, the function behaves like @Function.assign@ and $source$ is copied to $target$. 
..see:Function.assign
..include:seqan/basic.h
*/

template<typename TTarget, typename TSource>
inline void 
move(TTarget & target,
	 TSource & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}
template<typename TTarget, typename TSource>
inline void 
move(TTarget const & target,
	 TSource & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}
template<typename TTarget, typename TSource>
inline void 
move(TTarget & target,
	 TSource const & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}
template<typename TTarget, typename TSource>
inline void 
move(TTarget const & target,
	 TSource const & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}


//////////////////////////////////////////////////////////////////////////////
// set
//////////////////////////////////////////////////////////////////////////////

/**
.Function.set:
..summary:Assigns one object to another object avoiding to copy contents.
..cat:Content Manipulation
..signature:assign(target, source)
..signature:assign(target, source)
..param.target: Gets the content of $source$.
..param.source: Content source.
..remarks:$set(target, source)$ is semantically equivalent to $target = source$.
If possible, $set$ copies content references instead of the content itself.
..include:seqan/basic.h
*/

//TODO: rename set to ...

template<typename TTarget, typename TSource>
inline void 
set(TTarget & target,
	TSource & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}
template<typename TTarget, typename TSource>
inline void 
set(TTarget const & target,
	TSource & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}
template<typename TTarget, typename TSource>
inline void 
set(TTarget & target,
	TSource const & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}
template<typename TTarget, typename TSource>
inline void 
set(TTarget const & target,
	TSource const & source)
{
SEQAN_CHECKPOINT
	assign(target, source);
}


//////////////////////////////////////////////////////////////////////////////

} //namespace SEQAN_NAMESPACE_MAIN

#endif //#ifndef SEQAN_HEADER_...
