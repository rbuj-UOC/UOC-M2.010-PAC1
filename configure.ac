AC_PREREQ([2.71])

AC_INIT(g_compropietaris, 1.0, rbuj@uoc.edu)
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_CONFIG_SRCDIR([src/g_compropietaris.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strdup strstr])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

echo "
Configure summary:

	${PACKAGE_STRING}
	`echo $PACKAGE_STRING | sed "s/./=/g"`

	Source code location:      ${srcdir}
	Compiler:                  ${CC}
	Compiler flags:            ${CFLAGS}
	Warning flags:             ${WARN_CFLAGS}
	Linker flags:              ${LDFLAGS}
"
