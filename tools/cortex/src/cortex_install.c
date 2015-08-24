
#include "cortex_install.h"

static cx_bool cortex_validProject(void) {
	if (!cx_fileTest("rakefile")) {
		cx_error("cortex: need a valid project directory to install (no rakefile found)!");
		goto error;
	}
	return TRUE;
error:
	return FALSE;
}

static void cortex_promptPassword(void) {
	cx_pid pid = cx_procrun("sudo", (char*[]){"sudo", "true", NULL});
	cx_procwait(pid);
}

cx_int16 cortex_install(int argc, char *argv[]) {
	CX_UNUSED(argc);
	CX_UNUSED(argv);
	cx_bool buildingCortex = FALSE;

	if (!cortex_validProject()) {
		goto error;
	}

	/* Write installation script */
	FILE *install = fopen("install.sh", "w");
	if (!install) {
		cx_error("cortex: failed to create installation script (check permissions)");
		goto error;
	}

	/* Install build system from source */
	if (cx_fileTest("configure") && cx_fileTest("build")) {
		/* If installing cortex itself, install buildsystem */
		fprintf(install, "mkdir -p /usr/lib/cortex/%s\n", CORTEX_VERSION);
		fprintf(install, "cp -r ./build /usr/lib/cortex/%s\n", CORTEX_VERSION);
		buildingCortex = TRUE;
	}

	/* Set the build target to the global environment */
	fprintf(install, "export CORTEX_TARGET=/usr\n");
	fprintf(install, "export CORTEX_VERSION=%s\n", CORTEX_VERSION);
	fprintf(install, "export CORTEX_HOME=/usr/lib/cortex/%s\n", CORTEX_VERSION);
	fprintf(install, "export PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin\n");

	/* Build libraries to global environment */
	fprintf(install, "rake silent=true\n");

	if (buildingCortex) {
		/* Rename cortex */
		fprintf(install, "mv -f /usr/bin/cortex /usr/bin/cortex.%s\n", CORTEX_VERSION);
		fprintf(install, "ln -s /usr/bin/cortex.%s /usr/bin/cortex\n", CORTEX_VERSION);

		/* Rename libcortex.so */
		fprintf(install, "mv -f /usr/lib/libcortex.so /usr/lib/libcortex.so.%s\n", CORTEX_VERSION);
		fprintf(install, "ln -s /usr/lib/libcortex.so.%s /usr/lib/libcortex.so\n", CORTEX_VERSION);
	}

	fprintf(install, "rake clean 2> /dev/null\n");
	fclose(install);

	cortex_promptPassword();

	cx_pid pid = cx_procrun("sudo", (char*[]){"sudo", "sh", "install.sh", NULL});
	cx_char progress[] = {'|', '/', '-', '\\'};
	cx_int32 i = 0;
	printf("cortex: installing...  ");
	while(!cx_proccheck(pid)) {
		i++;
		printf("\b%c", progress[i % 4]);
		fflush(stdout);
		cx_sleep(0, 200000000);
	}
	cx_rm("install.sh");
	printf("\bdone!\n");

	return 0;
error:
	return -1;
}

cx_int16 cortex_uninstall(int argc, char *argv[]) {
	CX_UNUSED(argc);
	CX_UNUSED(argv);

	if (!cortex_validProject()) {
		goto error;
	}

	/* Write installation script */
	FILE *uninstall = fopen("uninstall.sh", "w");
	if (!uninstall) {
		cx_error("cortex: failed to create installation script (check permissions)");
		goto error;
	}

	/* Set the build target to the global environment */
	fprintf(uninstall, "export CORTEX_TARGET=/usr\n");
	fprintf(uninstall, "export CORTEX_VERSION=%s\n", CORTEX_VERSION);
	fprintf(uninstall, "export CORTEX_HOME=/usr/lib/cortex/%s\n", CORTEX_VERSION);
	fprintf(uninstall, "export PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin\n");

	fprintf(uninstall, "rake clobber 2> /dev/null\n");

	if (cx_fileTest("configure") && cx_fileTest("build")) {
		fprintf(uninstall, "rm -rf /usr/lib/cortex");
		fprintf(uninstall, "rm -rf ~/.cortex");
	}

	fclose(uninstall);

	cortex_promptPassword();

	cx_pid pid = cx_procrun("sudo", (char*[]){"sudo", "sh", "uninstall.sh", NULL});
	cx_char progress[] = {'|', '/', '-', '\\'};
	cx_int32 i = 0;
	printf("cortex: uninstalling...  ");
	while(!cx_proccheck(pid)) {
		i++;
		printf("\b%c", progress[i % 4]);
		fflush(stdout);
		cx_sleep(0, 200000000);
	}
	cx_rm("uninstall.sh");
	printf("\bdone!\n");

	return 0;
error:
	return -1;
}

cx_int16 cortex_locate(int argc, char* argv[]) {
	cx_string location;

	if (argc <= 1) {
		printf("cortex: please provide a package name\n");
		goto error;
	}

	location = cx_locate(argv[1]);

	if (location) {
		printf("cortex: '%s' => '%s'\n", argv[1], location);
	} else {
		printf("cortex: package '%s' not found\n", argv[1]);
		goto error;
	}

	return 0;
error:
	return -1;
}
