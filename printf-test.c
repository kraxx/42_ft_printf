#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int	main()
{
	printf("flag c for single character (int): %+-+-+-+ 00 000 000500.00000343c\n", 'C');

	printf("flag lc for wide single character (wint_t): %lc\n", 'C');

	printf("flag s for character string (char*): %s\n", "String");

	printf("flag ls for wide character string (wchar_t*): %ls\n", "String");
	
	printf("flag d for signed integer (int): %d\n", 69);
	
	printf("flag hhd for signed integer (signed char): %hhd\n", (signed char)69);
	
	printf("flag hd for signed integer (short): %hd\n", (short)69);
	
	printf("flag ld for signed integer (long): %ld\n", (long)69);

	printf("flag lld for signed integer (long long): %lld\n", (long long)69);
	
	printf("flag jd for signed integer (intmax_t): %jd\n", (intmax_t)69);
	
	printf("flag zd for signed integer (signed size_t): %zd\n", (size_t)69);
	
	printf("flag td for signed integer (ptrdiff_t): %td\n", (ptrdiff_t)69);
	
	printf("flag i for signed integer (int): %i\n", 69);
	
	printf("flag hhi for signed integer (signed char): %hhi\n", (signed char)69);
	
	printf("flag hi for signed integer (short): %hi\n", (short)69);
	
	printf("flag li for signed integer (long): %li\n", (long)69);

	printf("flag lli for signed integer (long long): %lli\n", (long long)69);
	
	printf("flag ji for signed integer (intmax_t): %ji\n", (intmax_t)69);
	
	printf("flag zi for signed integer (signed size_t): %zi\n", (size_t)69);
	
	printf("flag ti for signed integer (ptrdiff_t): %ti\n", (ptrdiff_t)69);
	
	printf("flag o for unsigned octal (int): %o\n", 69);
	
	printf("flag hho for unsigned octal (signed char): %hho\n", (signed char)69);
	
	printf("flag ho for unsigned octal (short): %ho\n", (short)69);
	
	printf("flag lo for unsigned octal (long): %lo\n", (long)69);

	printf("flag llo for unsigned octal (long long): %llo\n", (long long)69);
	
	printf("flag jo for unsigned octal (intmax_t): %jo\n", (intmax_t)69);
	
	printf("flag zo for unsigned octal (signed size_t): %zo\n", (size_t)69);
	
	printf("flag to for unsigned octal (ptrdiff_t): %to\n", (ptrdiff_t)69);

	printf("flag x for unsigned hex (int): %x\n", 69);

	printf("flag hhx for unsigned hex (signed char): %hhx\n", (signed char)69);
	
	printf("flag hx for unsigned hex (short): %hx\n", (short)69);
	
	printf("flag lx for unsigned hex (long): %lx\n", (long)69);

	printf("flag llx for unsigned hex (long long): %llx\n", (long long)69);
	
	printf("flag jx for unsigned hex (intmax_t): %jx\n", (intmax_t)69);
	
	printf("flag zx for unsigned hex (signed size_t): %zX\n", (size_t)255);
	
	printf("flag tx for unsigned hex (ptrdiff_t): %tX\n", (ptrdiff_t)69);

	printf("HUehuehuehue%s\n", "ay");
}
