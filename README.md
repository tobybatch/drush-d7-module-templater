Stubs out an empty module with a admin screen and a permissions hook.

    drush ntmt /path/to/some/some_module_name

Or for a full eaxmple (Country Hideaways)

    drush ntmt sites/all/modules/custom/ntch_modules/ntch_newmod \
       --admin_path=ntch \
       --package="Country Hideaways"  \
       --php_min_ver=5.5
