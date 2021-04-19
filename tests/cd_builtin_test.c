#include <criterion.h>

// CD CMD TEST
/*
**	Update OLDPWD AND PWD
**	save HOME
**	use case :
**	cd .
**	cd ..
**	cd -
*/

Test(cd_builtin, test_cd_pwd)
{}

Test(cd_builtin, test_absolute_path)
{}

Test(cd_builtin, test_cd_cwd)
{}
