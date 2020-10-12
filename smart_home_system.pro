TEMPLATE = subdirs

SUBDIRS += \
    qhttp-embed \
    smart_home_lib \
    smart_home_main \
    smart_home_tests

smart_home_main.depends = smart_home_lib qhttp-embed
smart_home_lib.depends = qhttp-embed
smart_home_tests.depends = smart_home_lib qhttp-embed
