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

#ifndef SEQAN_HEADER_BASIC_ITERATOR_BASE_H
#define SEQAN_HEADER_BASIC_ITERATOR_BASE_H

namespace SEQAN_NAMESPACE_MAIN
{
//////////////////////////////////////////////////////////////////////////////
// Iter
//////////////////////////////////////////////////////////////////////////////
/**
.Class.Iter:
..cat:Basic
..summary:Iterator that is used to traverse containers.
..signature:Iter<TContainer, TSpec>
..param.TContainer:Type of the container that can be iterated by $Iter$.
...metafunction:Metafunction.Container
..param.TSpec:The specializing type.
...metafunction:Metafunction.Spec
..implements:Concept.Iterator
..include:seqan/basic.h
*/
template <typename TContainer, typename TSpec>
class Iter;

//////////////////////////////////////////////////////////////////////////////
/**
.Metafunction.IterComplementConst:
..cat:Basic
..summary:Complement the "constness" of the container of an iterator.
..signature:IterComplementConst<TIterator>
..param.TIterator:The iterator to toggle the constness of its container for.
..include:seqan/basic.h
*/
template <typename TIterator>
struct IterComplementConst;

template <typename TContainer, typename TSpec>
struct IterComplementConst<Iter<TContainer, TSpec> >
{
    typedef Iter<
        typename If<
            IsSameType<typename RemoveConst_<TContainer>::Type, TContainer>::VALUE,
            TContainer const,
            typename RemoveConst_<TContainer>::Type>::Type,
        TSpec> Type;
};

template <typename TContainer, typename TSpec>
struct IterComplementConst<Iter<TContainer, TSpec> const>
        : IterComplementConst<Iter<TContainer, TSpec> > {};

//////////////////////////////////////////////////////////////////////////////
/**
.Metafunction.IterMakeConst:
..cat:Basic
..summary:Make the container of an Iter const.
..signature:IterMakeConst<TIterator>
..param.TIterator:The iterator make the container const for.
..include:seqan/basic.h
*/
template <typename TIterator>
struct IterMakeConst;

template <typename TContainer, typename TSpec>
struct IterMakeConst<Iter<TContainer, TSpec> >
{
    typedef Iter<typename RemoveConst_<TContainer>::Type const, TSpec> Type;
};

template <typename TContainer, typename TSpec>
struct IterMakeConst<Iter<TContainer, TSpec> const>
        : IterMakeConst<Iter<TContainer, TSpec> > {};

//////////////////////////////////////////////////////////////////////////////
///.Metafunction.Spec.param.T.type:Class.Iter

template <typename TContainer, typename TSpec>
struct Spec<Iter<TContainer, TSpec> >
{
	typedef TSpec Type;
};
template <typename TContainer, typename TSpec>
struct Spec<Iter<TContainer, TSpec> const>
{
	typedef TSpec Type;
};

//////////////////////////////////////////////////////////////////////////////

///.Metafunction.Value.param.T.type:Class.Iter

template <typename TContainer, typename TSpec>
struct Value<Iter<TContainer, TSpec> >:
	Value<TContainer>
{
};
template <typename TContainer, typename TSpec>
struct Value<Iter<TContainer, TSpec> const>:
	Value<TContainer>
{
};

//////////////////////////////////////////////////////////////////////////////

///.Metafunction.GetValue.param.T.type:Class.Iter

template <typename TContainer, typename TSpec>
struct GetValue<Iter<TContainer, TSpec> >:
	GetValue<TContainer>
{
};
template <typename TContainer, typename TSpec>
struct GetValue<Iter<TContainer, TSpec> const>:
	GetValue<TContainer>
{
};

//////////////////////////////////////////////////////////////////////////////

///.Metafunction.Reference.param.T.type:Class.Iter

template <typename TContainer, typename TSpec>
struct Reference<Iter<TContainer, TSpec> >:
	Reference<TContainer>
{
};
template <typename TContainer, typename TSpec>
struct Reference<Iter<TContainer, TSpec> const>:
	Reference<TContainer>
{
};

//////////////////////////////////////////////////////////////////////////////

///.Metafunction.Container.param.T.type:Class.Iter

template <typename T> struct Container;

template <typename TContainer, typename TSpec>
struct Container<Iter<TContainer, TSpec> >
{
	typedef TContainer Type;
};
template <typename TContainer, typename TSpec>
struct Container<Iter<TContainer, TSpec> const>
{
	typedef TContainer Type;
};

//////////////////////////////////////////////////////////////////////////////

/*
///.Metafunction.Host.param.T.type:Class.Iter

template <typename TContainer, typename TSpec>
struct Host<Iter<TContainer, TSpec> >:
	Container<Iter<TContainer, TSpec> >
{
};
template <typename TContainer, typename TSpec>
struct Host<Iter<TContainer, TSpec> const>:
	Container<Iter<TContainer, TSpec> const>
{
};
*/

//////////////////////////////////////////////////////////////////////////////
// operator *
//////////////////////////////////////////////////////////////////////////////

template <typename TContainer, typename TSpec>
inline typename Reference<Iter<TContainer, TSpec> >::Type
operator * (Iter<TContainer, TSpec> & me)
{
SEQAN_CHECKPOINT
	return value(me);
}
template <typename TContainer, typename TSpec>
inline typename Reference<Iter<TContainer, TSpec> const>::Type
operator * (Iter<TContainer, TSpec> const & me)
{
SEQAN_CHECKPOINT
	return value(me);
}

//////////////////////////////////////////////////////////////////////////////
// operator ++
//////////////////////////////////////////////////////////////////////////////

template <typename TContainer, typename TSpec>
inline Iter<TContainer, TSpec> const &
operator ++ (Iter<TContainer, TSpec> & me)
{
SEQAN_CHECKPOINT
	goNext(me);
	return me;
}

template <typename TContainer, typename TSpec>
inline Iter<TContainer, TSpec>
operator ++ (Iter<TContainer, TSpec> & me, int)
{
SEQAN_CHECKPOINT
	Iter<TContainer, TSpec> temp_(me);
	goNext(me);
	return temp_;
}

//////////////////////////////////////////////////////////////////////////////
// operator --
//////////////////////////////////////////////////////////////////////////////

template <typename TContainer, typename TSpec>
inline Iter<TContainer, TSpec> const &
operator -- (Iter<TContainer, TSpec> & me)
{
SEQAN_CHECKPOINT
	goPrevious(me);
	return me;
}

template <typename TContainer, typename TSpec>
inline Iter<TContainer, TSpec>
operator -- (Iter<TContainer, TSpec> & me, int)
{
SEQAN_CHECKPOINT
	Iter<TContainer, TSpec> temp_(me);
	goPrevious(me);
	return temp_;
}

//////////////////////////////////////////////////////////////////////////////
// operator + / +=
//////////////////////////////////////////////////////////////////////////////
/*
template <typename TContainer, typename TSpec, typename TSize>
inline Iter<TContainer, TSpec>
operator + (Iter<TContainer, TSpec> & me, TSize size)
{
SEQAN_CHECKPOINT
	Iter<TContainer, TSpec> temp_(me);
	goFurther(temp_, size);
	return temp_;
}
*/
template <typename TContainer, typename TSpec, typename TSize>
inline Iter<TContainer, TSpec>
operator + (Iter<TContainer, TSpec> const & me, TSize size)
{
SEQAN_CHECKPOINT
	Iter<TContainer, TSpec> temp_(me);
	goFurther(temp_, size);
	return temp_;
}

template <typename TContainer, typename TSpec, typename TSize>
inline Iter<TContainer, TSpec> const &
operator += (Iter<TContainer, TSpec> & me, TSize size)
{
SEQAN_CHECKPOINT
	goFurther(me, size);
	return me;
}

//////////////////////////////////////////////////////////////////////////////
// operator - / -=
//////////////////////////////////////////////////////////////////////////////
/* // collides with Iter-Iter
template <typename TContainer, typename TSpec, typename TSize>
inline Iter<TContainer, TSpec>
operator - (Iter<TContainer, TSpec> & me, TSize size)
{
SEQAN_CHECKPOINT
	Iter<TContainer, TSpec> temp_(me);
	goFurther(temp_, -size);
	return temp_;
}

template <typename TContainer, typename TSpec, typename TSize>
inline Iter<TContainer, TSpec>
operator - (Iter<TContainer, TSpec> const & me, TSize size)
{
SEQAN_CHECKPOINT
	Iter<TContainer, TSpec> temp_(me);
	goFurther(temp_, -size);
	return temp_;
}

template <typename TContainer, typename TSpec, typename TSize>
inline Iter<TContainer, TSpec> const &
operator -= (Iter<TContainer, TSpec> & me, TSize size)
{
SEQAN_CHECKPOINT
	goFurther(me, -size);
	return me;
}
*/
//////////////////////////////////////////////////////////////////////////////
// position
//////////////////////////////////////////////////////////////////////////////

//most Iter classes are rooted strings

template <typename TContainer, typename TSpec, typename TContainer2>
inline typename Position<Iter<TContainer, TSpec> const>::Type
position(Iter<TContainer, TSpec> const & me,
		 TContainer2 const &)
{
SEQAN_CHECKPOINT
	return position(me);
}


//////////////////////////////////////////////////////////////////////////////

} //namespace SEQAN_NAMESPACE_MAIN

#endif //#ifndef SEQAN_HEADER_...
