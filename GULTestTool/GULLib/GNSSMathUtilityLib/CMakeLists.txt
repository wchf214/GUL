aux_source_directory(DllMain src_interface)
aux_source_directory(AppIFs  src_imp)

add_library(GulMath SHARED ${src_imp} ${src_interface})