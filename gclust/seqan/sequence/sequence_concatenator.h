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
// Author: David Weese <david.weese@fu-berlin.de>
// ==========================================================================
// A lightweight wrapper object around StringSet objects that makes the
// behave like ConcatDirect StringSets.  This mainly affects the Iterator
// metafunction and iterator-related functions such as begin(), end().
// ==========================================================================

#ifndef SEQAN_SEQUENCE_STRING_SET_CONCATENATOR_H_
#define SEQAN_SEQUENCE_STRING_SET_CONCATENATOR_H_

namespace seqan {

// ============================================================================
// Forwards
// ============================================================================

// ============================================================================
// Tags, Classes, Enums
// ============================================================================

/**
.Class.ConcatenatorManyToOne:
..summary:A sequence class that virtually concatenates all sequences in a @Class.StringSet@.
..cat:Sequences
..signature:ConcatenatorManyToOne<TStringSet>
..param.TStringSet:The @Class.StringSet@ type.
...type:Class.StringSet
..remarks:This container can be iterated like the concatenation string of all sequences in a @Class.StringSet@.
..remarks:This container only is a lightweight hull around a @Class.StringSet@. The iteration is handled by @Spec.ConcatVirtual Iterator@.
..remarks:Note that accessing an element by index through $operator[]$ conducts a binary search and should be avoided. Use the @Spec.ConcatDirect@ specialization of @Class.StringSet@ for random access or only use sequential access through iterators.
..include:seqan/sequence.h
.Memfunc.ConcatenatorManyToOne#ConcatenatorManyToOne
..summary:Constructor
..signature:ConcatenatorManyToOne<TStringSet> (stringSet)
..param.stringSet:The @Class.StringSet@ object to be concatenated.
..class:Class.ConcatenatorManyToOne
 */
template <typename TStringSet>
class ConcatenatorManyToOne
{
public:
    // TODO(holtgrew): Why is this no holder? const-holder problem?
    TStringSet * set;
    ConcatenatorManyToOne() {}
    ConcatenatorManyToOne(TStringSet & _set) : set(&_set) {}

    template <typename TPos>
    inline typename Reference<ConcatenatorManyToOne>::Type
    operator[] (TPos pos)
    {
        SEQAN_CHECKPOINT;
        return value(*this, pos);
    }

    template <typename TPos>
    inline typename Reference<ConcatenatorManyToOne const>::Type
    operator[] (TPos pos) const
    {
        SEQAN_CHECKPOINT;
        return value(*this, pos);
    }
};

// ============================================================================
// Metafunctions
// ============================================================================

// --------------------------------------------------------------------------
// Metafunction Iterator
// --------------------------------------------------------------------------

template <typename TString, typename TSpec >
struct Iterator<ConcatenatorManyToOne<StringSet<TString, TSpec> >, Standard>
{
    typedef Iter<StringSet<TString, TSpec>, ConcatVirtual<> > Type;
};

template <typename TString, typename TSpec >
struct Iterator<ConcatenatorManyToOne<StringSet<TString, TSpec> const>, Standard>
{
    typedef Iter<StringSet<TString, TSpec> const, ConcatVirtual<> > Type;
};

template <typename TStringSet >
struct Iterator<ConcatenatorManyToOne<TStringSet> const, Standard>
{
    typedef typename Iterator<ConcatenatorManyToOne<TStringSet>, Standard>::Type Type;
};

template <typename TString, typename TSpec >
struct Iterator<ConcatenatorManyToOne<StringSet<TString, TSpec> >, Rooted>
{
    typedef Iter<StringSet<TString, TSpec>, ConcatVirtual<> > Type;
};

template <typename TString, typename TSpec >
struct Iterator<ConcatenatorManyToOne<StringSet<TString, TSpec> const>, Rooted>
{
    typedef Iter<StringSet<TString, TSpec> const, ConcatVirtual<> > Type;
};

template <typename TStringSet >
struct Iterator<ConcatenatorManyToOne<TStringSet> const, Rooted>
{
    typedef typename Iterator<ConcatenatorManyToOne<TStringSet>, Rooted>::Type Type;
};

// --------------------------------------------------------------------------
// Metafunction Value
// --------------------------------------------------------------------------

template <typename TStringSet>
struct Value<ConcatenatorManyToOne<TStringSet> >
{
    typedef typename Value<typename Value<TStringSet>::Type >::Type Type;
};

template <typename TStringSet>
struct Value<ConcatenatorManyToOne<TStringSet> const >
    : Value<ConcatenatorManyToOne<TStringSet> > {};

// --------------------------------------------------------------------------
// Metafunction Size
// --------------------------------------------------------------------------

template <typename TStringSet>
struct Size<ConcatenatorManyToOne<TStringSet> >
{
    typedef typename Size<typename Value<TStringSet>::Type >::Type Type;
};

// --------------------------------------------------------------------------
// Metafunction AllowsFastRandomAccess
// --------------------------------------------------------------------------

template <typename TStringSet>
struct AllowsFastRandomAccess<ConcatenatorManyToOne<TStringSet> >
{
    typedef False Type;
    enum { VALUE = false };
};

// ============================================================================
// Functions
// ============================================================================

// --------------------------------------------------------------------------
// Function value()
// --------------------------------------------------------------------------

template <typename TStringSet, typename TPos >
inline typename Reference<ConcatenatorManyToOne<TStringSet> >::Type
value(ConcatenatorManyToOne<TStringSet> & me, TPos globalPos)
{
    Pair<unsigned, typename Size<typename Value<TStringSet>::Type >::Type> localPos;
    posLocalize(localPos, globalPos, stringSetLimits(*me.set));
    return value(value(*me.set, getValueI1(localPos)), getValueI2(localPos));
}

template <typename TStringSet, typename TPos >
inline typename Reference<ConcatenatorManyToOne<TStringSet> const >::Type
value(ConcatenatorManyToOne<TStringSet> const & me, TPos globalPos)
{
    typedef typename Value<TStringSet>::Type TString;
    Pair<unsigned, typename Size<TString>::Type> localPos;
    posLocalize(localPos, globalPos, stringSetLimits(*me.set));
    return value(value(*(TStringSet const*)me.set, getValueI1(localPos)), getValueI2(localPos));
}

// --------------------------------------------------------------------------
// Function length()
// --------------------------------------------------------------------------

template <typename TStringSet >
inline typename Size<ConcatenatorManyToOne<TStringSet> >::Type
length(ConcatenatorManyToOne<TStringSet> const & me)
{
    return lengthSum(*me.set);
}

// --------------------------------------------------------------------------
// Function begin()
// --------------------------------------------------------------------------

template <typename TStringSet, typename TSpec >
inline typename Iterator<ConcatenatorManyToOne<TStringSet const>, Tag<TSpec> const>::Type
begin(ConcatenatorManyToOne<TStringSet const> concat, Tag<TSpec> const &)
{
    typedef typename Iterator<ConcatenatorManyToOne<TStringSet const>, Tag<TSpec> const>::Type TIter;
    return TIter(*concat.set);
}

template <typename TStringSet, typename TSpec >
inline typename Iterator<ConcatenatorManyToOne<TStringSet>, Tag<TSpec> const>::Type
begin(ConcatenatorManyToOne<TStringSet> concat, Tag<TSpec> const &)
{
    typedef typename Iterator<ConcatenatorManyToOne<TStringSet>, Tag<TSpec> const>::Type TIter;
    return TIter(*concat.set);
}

// --------------------------------------------------------------------------
// Function end()
// --------------------------------------------------------------------------

template <typename TStringSet, typename TSpec >
inline typename Iterator<ConcatenatorManyToOne<TStringSet const>, Tag<TSpec> const>::Type
end(ConcatenatorManyToOne<TStringSet const> concat, Tag<TSpec> const &)
{
    typedef typename Iterator<ConcatenatorManyToOne<TStringSet>, Tag<TSpec> const >::Type TIter;
    return TIter(*concat.set, length(*concat.set), 0);
}

template <typename TStringSet, typename TSpec >
inline typename Iterator<ConcatenatorManyToOne<TStringSet>, Tag<TSpec> const>::Type
end(ConcatenatorManyToOne<TStringSet> concat, Tag<TSpec> const &)
{
    typedef typename Iterator<ConcatenatorManyToOne<TStringSet>, Tag<TSpec> const>::Type TIter;
    return TIter(*concat.set, length(*concat.set), 0);
}

}  // namespace seqan

#endif  // #ifndef SEQAN_SEQUENCE_STRING_SET_CONCATENATOR_H_
