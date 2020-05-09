aux_source_directory(DllMain src_interface)
aux_source_directory(AppIFs  src_imp)
aux_source_directory(Time src_time)
aux_source_directory(Ephemeris src_eph)
aux_source_directory(Coordinate src_coord)
aux_source_directory(Angle src_angle)

add_library(GulUtility SHARED ${src_interface} ${src_imp} ${src_time} ${src_eph} ${src_coord} ${src_angle})