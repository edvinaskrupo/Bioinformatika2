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
// Author: Andreas Gogol-Doering <andreas.doering@mdc-berlin.de>
// ==========================================================================
// Implementation of the Alloc string class.
// ==========================================================================

#ifndef SEQAN_HEADER_SEQUENCE_STRING_ALLOC_H
#define SEQAN_HEADER_SEQUENCE_STRING_ALLOC_H

namespace seqan {

// ============================================================================
// Forwards
// ============================================================================

// ============================================================================
// Tags, Classes, Enums
// ============================================================================

// TODO(holtgrew): Where is Alloc<> defined? In module base?

/**
.Spec.Alloc String:
..cat:Strings
..general:Class.String
..summary:Expandable string that is stored on heap.
..signature:String<TValue, Alloc<TSpec> >
..param.TValue:The value type, that is the type of the items/characters stored in the string.
...remarks:Use @Metafunction.Value@ to get the value type for a given class.
..param.TSpec:The specializing type.
...default:$void$
..include:seqan/sequence.h
*/
template <typename TValue>
class String<TValue, Alloc<void> >
{
public:
    typename Value<String>::Type * data_begin;
    typename Value<String>::Type * data_end;
    size_t data_capacity;

    String():
        data_begin(0),
        data_end(0),
        data_capacity(0)
    {
        SEQAN_CHECKPOINT;
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
    }

    template <typename TSource>
    String(TSource & source):
        data_begin(0),
        data_end(0),
        data_capacity(0)
    {
        SEQAN_CHECKPOINT;
        assign(*this, source);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
    }
    
    template <typename TSource>
    String(TSource const & source):
        data_begin(0),
        data_end(0),
        data_capacity(0)
    {
        SEQAN_CHECKPOINT;
        assign(*this, source);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
    }
    
    String(String const & source):
        data_begin(0),
        data_end(0),
        data_capacity(0)
    {
        SEQAN_CHECKPOINT;
        assign(*this, source);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
    }
    
    String(String & source, Move const &):
        data_begin(0),
        data_end(0),
        data_capacity(0)
    {
        SEQAN_CHECKPOINT;
        move(*this, source);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
    }
    
    template <typename TSource, typename TSize>
    String(TSource & source, TSize limit):
        data_begin(0),
        data_end(0),
        data_capacity(0)
    {
        SEQAN_CHECKPOINT;
        assign(*this, source, limit);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
    }
    
    template <typename TSource, typename TSize>
    String(TSource const & source, TSize limit):
        data_begin(0),
        data_end(0),
        data_capacity(0)
    {
        SEQAN_CHECKPOINT;
        assign(*this, source, limit);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
    }


    template <typename TSource>
    String & operator =(TSource const & source)
    {
        SEQAN_CHECKPOINT;
        assign(*this, source);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
        return *this;
    }
    
    String & operator =(String const & source)
    {
        SEQAN_CHECKPOINT;
        assign(*this, source);
        SEQAN_ASSERT_LEQ_MSG(data_begin, data_end, "String end is before begin!");
        return *this;
    }

    ~String()
    {
        SEQAN_CHECKPOINT;
        arrayDestruct(this->data_begin, this->data_end);
        _deallocateStorage(*this, this->data_begin, data_capacity);
    }

    // ----------------------------------------------------------------------
    // Subscription operators; have to be defined in class def.
    // ----------------------------------------------------------------------

    template <typename TPos>
    inline typename Reference<String>::Type
    operator [] (TPos pos)
    {
SEQAN_CHECKPOINT
        return value(*this, pos);
    }

    template <typename TPos>
    inline typename Reference<String const>::Type
    operator [] (TPos pos) const
    {
SEQAN_CHECKPOINT
        return value(*this, pos);
    }
};

// ============================================================================
// Functions
// ============================================================================

template <typename TValue, typename TSpec>
inline typename Iterator<String<TValue, Alloc<TSpec> >, Standard>::Type
begin(String<TValue, Alloc<TSpec> > & me,
    Standard)
{
SEQAN_CHECKPOINT
    return me.data_begin;
}
template <typename TValue, typename TSpec>
inline typename Iterator<String<TValue, Alloc<TSpec> > const, Standard>::Type
begin(String<TValue, Alloc<TSpec> > const & me,
    Standard)
{
SEQAN_CHECKPOINT
    return me.data_begin;
}

//____________________________________________________________________________

template <typename TValue, typename TSpec>
inline typename Iterator<String<TValue, Alloc<TSpec> >, Standard>::Type
end(String<TValue, Alloc<TSpec> > & me,
    Standard)
{
SEQAN_CHECKPOINT
    return me.data_end;
}
template <typename TValue, typename TSpec>
inline typename Iterator<String<TValue, Alloc<TSpec> > const, Standard>::Type
end(String<TValue, Alloc<TSpec> > const & me,
    Standard)
{
SEQAN_CHECKPOINT
    return me.data_end;
}

//____________________________________________________________________________

template <typename TValue, typename TSpec>
inline size_t
capacity(String<TValue, Alloc<TSpec> > & me)
{
SEQAN_CHECKPOINT
    return me.data_capacity;
}

template <typename TValue, typename TSpec>
inline size_t
capacity(String<TValue, Alloc<TSpec> > const & me)
{
SEQAN_CHECKPOINT
    return me.data_capacity;
}

//____________________________________________________________________________
/* Entwicklungsschrott?
inline void
move(String & target,
     String & source)
{
    clear(target);
    target.data_begin = source.data_begin;
    target.data_end = source.data_end;
    target.data_capacity = source.data_capacity;

    source.data_begin = 0;
    source.data_end = 0;
    source.data_capacity = 0;
}
*/
//____________________________________________________________________________

/**
.Internal._setBegin:
*/
template <typename TValue, typename TSpec, typename TPtr>
inline void
_setBegin(
    String<TValue, Alloc<TSpec> > & me,
    TPtr * new_begin)
{
SEQAN_CHECKPOINT
    me.data_begin = new_begin;
}

//____________________________________________________________________________

/**
.Internal._setLength:
..cat:Functions
..summary:Set the length of container.
..signature:_setLength(object, new_length)
..param.object:A container.
..param.object.type:Spec.Alloc String
..param.new_length:The new length.
*/
template <typename TValue, typename TSpec>
inline void
_setLength(
    String<TValue, Alloc<TSpec> > & me,
    size_t new_length)
{
SEQAN_CHECKPOINT
    me.data_end = me.data_begin + new_length;
}

//____________________________________________________________________________

/**
.Internal._setCapacity:
*/
template <typename TValue, typename TSpec>
inline void
_setCapacity(
    String<TValue, Alloc<TSpec> > & me,
    size_t new_capacity)
{
SEQAN_CHECKPOINT
    me.data_capacity = new_capacity;
}

//____________________________________________________________________________

/**
.Internal._allocateStorage:
..cat:Functions
..summary:Allocates a new buffer for a container.
..signature:_allocateStorage(object, new_capacity)
..param.object:A container.
..param.object.type:Spec.Alloc String
..param.new_capacity:The capacity of the new allocated buffer.
..returns:The old butter $object$, that is replaced by the new allocated buffer.
..remarks:The returned buffer must be deallocated by @Internal._deallocateStorage@.
..remarks:This function does not construct objects in the allocated buffer.
..see:Internal._reallocateStorage
*/
template <typename TValue, typename TSpec>
inline typename Value<String<TValue, Alloc<TSpec> > >::Type *
_allocateStorage(
    String<TValue, Alloc<TSpec> > & me,
    size_t new_capacity)
{
SEQAN_CHECKPOINT
    size_t size = _computeSizeForCapacity(me, new_capacity);
    typename Value<String<TValue, Alloc<TSpec> > >::Type * _returnValue = me.data_begin;
    allocate(me, me.data_begin, size, TagAllocateStorage());
    me.data_capacity = new_capacity;
    return _returnValue;
}

//____________________________________________________________________________

/**
.Internal._deallocateStorage:
..cat:Functions
..summary:Deallocates a buffer of a container.
..signature:_deallocateStorage(object, buffer, capacity)
..param.object:A container.
..param.object.type:Spec.Alloc String
..param.buffer:The buffer that will be deallocated.
..param.capacity:The capacity of $buffer$.
..remarks:All objects in the buffer must be destroyed before calling $_deallocateStorage$.
..see:Internal._allocateStorage
..see:Internal._reallocateStorage
*/
template <typename TValue, typename TSpec, typename TPtr>
inline void
_deallocateStorage(
    String<TValue, Alloc<TSpec> > & me,
    TPtr * ptr,
    size_t capacity)
{
SEQAN_CHECKPOINT
    size_t size = _computeSizeForCapacity(me, capacity);
    deallocate(me, ptr, size, TagAllocateStorage());
}

//////////////////////////////////////////////////////////////////////////////

template <typename TValue, typename TSpec>
struct DefaultOverflowImplicit<String<TValue, Alloc<TSpec> > >
{
    typedef Generous Type;
};

template <typename TValue, typename TSpec>
struct DefaultOverflowImplicit<String<TValue, Alloc<TSpec> > const >
{
    typedef Generous Type;
};

//////////////////////////////////////////////////////////////////////////////

template <typename TValue, typename TSpec>
struct IsContiguous< String<TValue, Alloc<TSpec> > >
{
    typedef True Type;
    enum { VALUE = true };
};


//////////////////////////////////////////////////////////////////////////////

template <typename TTargetValue, typename TSourceValue, typename TSpec>
inline void
move(String<TTargetValue, Alloc<TSpec> > & target,
     String<TSourceValue, Alloc<TSpec> > & source)
{
    _moveContiguous(target, source);
}
template <typename TTargetValue, typename TSourceValue, typename TSpec>
inline void
move(String<TTargetValue, Alloc<TSpec> > & target,
     String<TSourceValue, Alloc<TSpec> > const & source)
{
    _moveContiguous(target, source);
}

template <typename TValue, typename TSpec>
inline void
move(String<TValue, Alloc<TSpec> > & target,
     String<TValue, Alloc<TSpec> > & source)
{
    clear(target);
    target.data_begin = source.data_begin;
    target.data_end = source.data_end;
    target.data_capacity = source.data_capacity;

    source.data_begin = 0;
    source.data_end = 0;
    source.data_capacity = 0;
}

template <typename TValue, typename TSpec>
inline void
move(String<TValue, Alloc<TSpec> > & target,
     String<TValue, Alloc<TSpec> > const & source)
{
    move(target, const_cast<String<TValue, Alloc<TSpec> > &>(source));
}

} // namespace seqan

#endif //#ifndef SEQAN_HEADER_...
