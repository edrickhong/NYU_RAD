#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef char s8;
typedef short s16;
typedef int s32;

typedef float f32;
typedef double f64;


typedef unsigned long long u64;
typedef long long s64;


typedef u64 b64;
typedef u32 b32;
typedef u16 b16;
typedef u8 b8;

typedef unsigned int ptrsize;


#ifndef __cplusplus
#define true 1
#define false 0
#endif


#define _deprecated __attribute__((deprecated))
#define _restrict __restrict__
#define _ainline inline __attribute__((always_inline))
#define _align(alignment) __attribute__((aligned(alignment)))
#define _membarrier() asm volatile("" : : : "memory")
#define _winapi
#define _dllexport __attribute__((visibility("default")))
#define _packed __attribute__((packed))
#define _breakpoint() __asm__ volatile("int $3\n")


#define _cachealign _align(64)

#define _either(condition, value1, value2) ((condition) ? value1 : value2)
#define _intern static
#define _persist static
#define _global static
#define _countsize(size, type) size / (sizeof(type))
#define _typebitcount(a) (sizeof(a) * 8)
#define _arraycount(ar) (sizeof(ar) / sizeof(ar[0]))
#define _in_
#define _out_
#define _optnl_

#define _writetop16(m64t, value) (m64t.u | (((u64)value) << 48))
#define _gettop16(m64t) (m64t.u >> 48)
#define _masktop16(m64t) (m64t.u ^ 0xFFFF000000000000)
#define _zerotop16(m64t) (m64t.u ^= 0xFFFF000000000000)

#define _unsigned_max(value) (((u64)1 << (sizeof(value) * 8)) - 1)
#define _unsigned_max8 _unsigned_max(u8)
#define _unsigned_max16 _unsigned_max(u16)
#define _unsigned_max32 _unsigned_max(u32)
#define _unsigned_max64 _unsigned_max(u64)

#define _signed_min(value) ((s64)(_unsigned_max(value)))
#define _signed_min8 _signed_min(s8)
#define _signed_min16 _signed_min(s16)
#define _signed_min32 _signed_min(s32)
#define _signed_min64 _signed_min(s64)

#define _signed_max(value) (~(_signed_min(value)))
#define _signed_max8 _signed_max(s8)
#define _signed_max16 _signed_max(s16)
#define _signed_max32 _signed_max(s32)
#define _signed_max64 _signed_max(s64)

#define _kilobytes(value) ((value)*1024)
#define _megabytes(value) (_kilobytes(value) * 1024)
#define _gigabytes(value) (_megabytes((uint64_t)value) * 1024)
#define _terrabytes(value) (_gigabytes((uint64_t)value) * 1024)

#define _alignpow2(value, pow) ((value + (pow - 1)) & (~(pow - 1)))
#define _align4(value) _alignpow2(value, 4)
#define _align8(value) _alignpow2(value, 8)
#define _align16(value) _alignpow2(value, 16)
#define _align32(value) _alignpow2(value, 32)
#define _align64(value) _alignpow2(value, 64)
#define _align128(value) _alignpow2(value, 128)
#define _align256(value) _alignpow2(value, 256)
#define _devicealign(value) _align256(value)
#define _mapalign(value) _align128(value)

// kind of like rounding down by power of 2
#define _dalignpow2(value, pow) ((value) & (~(pow - 1)))
#define _dmapalign(value) _dalignpow2(value, 128)

#define _encode_bgra(b, g, r, a) \
	(((a)) | (((r)) << 8) | (((g)) << 16) | (((b)) << 24))
#define _encode_rgba(r, g, b, a) \
	(((a)) | (((b)) << 8) | (((g)) << 16) | (((r)) << 24))
#define _encode_argb(a, r, g, b) \
	(((b)) | (((g)) << 8) | (((r)) << 16) | (((a)) << 24))

#define _removesignedbit(value) (value & 0x7FFFFFFF)
#define _addsignedbit(value) (value | (1 << 31))

#ifdef DEBUG

#define _kill(string, condition)                                        \
	if ((condition)) {                                              \
		printf("%s %s %d\n", __FUNCTION__, __FILE__, __LINE__); \
		*(int*)0 = 0;                                           \
	}
#define _dprint(string, ...) printf(string, __VA_ARGS__);
#define _impl_PASTE(a, b) a##b
#define _impl_CASSERT_LINE(predicate, line, file)            \
	typedef char _impl_PASTE(assertion_failed_##file##_, \
				 line)[2 * !!(predicate)-1];
#define _compile_kill(condition) \
	_impl_CASSERT_LINE(!(condition), __LINE__, __FILE__)

#else

#define _kill(string, condition)
#define _compile_kill(condition)
#define _dprint(string, ...)

#endif

typedef union {
	u32 u;
	s32 i;
	f32 f;

	u8 byte[4];
	u16 word[2];

	s8 sbyte[4];
	s16 sword[2];

#ifdef __cplusplus

	operator u32() { return u; }

	operator s32() { return i; }

	operator f32() { return f; }

	void operator=(u32 o) { u = o; }

	void operator=(f32 o) { f = o; }

#endif

} m32;

typedef struct {
	union {
		u64 u;
		s64 i;
		f64 f;

		u8 byte[8];
		u16 word[4];
		u32 dword[4];

		s8 sbyte[8];
		s16 sword[4];
		s32 sdword[4];

		m32 array[2];
		//__m64 m;

		void* ptr;
	};

	u32 pad1;
	u16 pad2;
	u16 top16_bits;

#ifdef __cplusplus

	m32& operator[](ptrsize index) { return array[index]; }

	operator u64() { return u; }

	operator s64() { return i; }

	operator f64() { return f; }

	void operator=(u64 o) { u = o; }

	void operator=(f64 o) { f = o; }

#endif
} m64;

void _ainline ClearPtrTop16Bits(void** ptr) {
	m64 v = {0};
	v.ptr = *ptr;

	v.u ^= 0xFFFF000000000000;

	*ptr = v.ptr;
}

void _ainline WritePtrTop16Bits(void** ptr, u16 value) {
	ClearPtrTop16Bits(ptr);

	m64 v = {0};
	v.ptr = *ptr;

	v.u |= ((u64)value) << 48;

	*ptr = v.ptr;
}

u16 _ainline GetPtrTop16Bits(void* ptr) {
	m64 v = {0};
	v.ptr = ptr;

	return (v.u >> 48);
}

_ainline void* MaskPtrTop16Bits(void* ptr) {
	ClearPtrTop16Bits(&ptr);

	return ptr;
}

//This is for documentation:
#ifdef CPP_PASS
#define REFDOC(...) REFDOC(...)
#else
#define REFDOC(...)
#endif
