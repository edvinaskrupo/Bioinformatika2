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

#ifndef SEQAN_HEADER_BASIC_VOLATILE_PTR_H
#define SEQAN_HEADER_BASIC_VOLATILE_PTR_H

//////////////////////////////////////////////////////////////////////////////

namespace SEQAN_NAMESPACE_MAIN
{

	//////////////////////////////////////////////////////////////////////////////
	// volatile pointer
	// allows you to handle volatile data (used by ext. string during swapping)
    //
	// imagine volatile pointers as nodes in an undirected graph
    // when you assign one to another then they are connected
    // all pointers in a connection component points to the same value
    // by calling nukeCopies you can destroy the component and set all pointers to NULL

	template < typename Type >
	struct VolatilePtr
	{
		typedef VolatilePtr		Self_;
		typedef VolatilePtr*	SelfPtr_;
		typedef VolatilePtr&	SelfRef_;

		typedef Type&			reference;
		typedef const Type&		const_reference;
		typedef Type*			pointer;

		pointer			ptr;
		SelfPtr_		next;			// prev == NULL means this is the master node
		SelfPtr_		prev;			// prev == NULL means this is the master node

        VolatilePtr() {	    // volatile pinters behave like normal pointers
            prev = this;    // and are not initialized (ptr) per default
            next = this;
        }

        VolatilePtr(const pointer _p) {
			ptr = _p;
			prev = this;
			next = this;
        }

        VolatilePtr(const Self_& _vp) {
			ptr = _vp.ptr;
			prev = this;
			next = this;
        }

        VolatilePtr(SelfRef_ _vp) {
			ptr = _vp.ptr;
			prev = this;
			next = this;
			if (ptr) hangOn(_vp);
		}

		~VolatilePtr() {
			hangOff();
		}
        
        template <typename size_type>
		inline reference operator[] (size_type offset) {
			return ptr[offset];
		}

        template <typename size_type>
		inline const_reference operator[] (size_type offset) const {
			return ptr[offset];
		}

		inline Self_& operator=(Self_ const &Right_) {
			hangOff();
			ptr = Right_.ptr;
            if (ptr) hangOn(const_cast<Self_&>(Right_));
			return *this;
		}

		inline Self_& operator=(pointer const Right_) {
			hangOff();
			ptr = Right_;
			return *this;
		}

        inline bool isLonely() {
            return next == this;
        }

		inline void nukeCopies() {
			SelfPtr_ p = next;
			while (p != this) {
				SelfPtr_ tmp = p->next;
				p->ptr = NULL;
				p->prev = p;
				p->next = p;
				p = tmp;
			}
            prev = this;
			next = this;
		}

		inline bool operator== (const Self_ &I) const {
			return ptr == I.ptr;
		}

		inline bool operator!= (const Self_ &I) const {
			return ptr != I.ptr;
		}

		inline operator pointer () const {
			return ptr;
		}

	private:

		inline void hangOn(SelfRef_ _prev) {
			// hang on between _prev and _prev.next
			prev = &_prev;
			next = _prev.next;
			_prev.next = this;
			next->prev = this;
		}

		inline void hangOff() {
			next->prev = prev;
			prev->next = next;
            next = this;
            prev = this;
		}
	};

    template <typename TValue>
    inline void nukeCopies(TValue* &) {}

    template <typename TValue>
    inline void nukeCopies(VolatilePtr<TValue> &ptr) { ptr.nukeCopies(); }

}

#endif
