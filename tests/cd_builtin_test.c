
#include <criterion.h>
#include "../includes/header.h"

// CD CMD TEST
/*
**	Update OLDPWD AND PWD
**	save HOME
**	use case :
**	cd .
**	cd ..
**	cd ~
**	cd -
*/



char	*get_home_var(t_list **env_list);
int		update_oldpwd(t_list **env_list, char *oldpwd);
int		update_pwd(t_list **env_list, char *pwd);
int		change_directory(t_list **env_list, char *new_path);

Test(cd_builtin, get_home_var_fct)
{
	t_dict	home;
	home->key = strdup("HOME");
	home->value = strdup("/bonjour/example");

	t_list	test;
	test->content = &home;
	test->next = NULL;

	//normal behaviour
	cr_assert_str_eq(get_home_var(&test), home->value);

	cr_free(home->key);
	home->key = strdup("HOMIE");
	test->content = &home;

	//if home does not exis 
	// ShoulDnOtHappeN
	cr_assert_null(get_home_var(&test));
}

Test(cd_builtin, change_directory)
{	
}
