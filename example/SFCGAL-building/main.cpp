#include <SFCGAL/all.h>

#include <SFCGAL/config.h>

#include <SFCGAL/io/wkt.h>
#include <SFCGAL/detail/generator/building.h>

// optional osg support for outputs
#ifdef SFCGAL_WITH_OSG
#include <SFCGAL/io/osg.h>
#endif

using namespace SFCGAL ;

int main(){
	std::vector< std::string > wkts ;
	wkts.push_back( "POLYGON((202043.6 6816168.3,202036.6 6816166.8,202035.6 6816155.5,202040.2 6816153.5,202043.2 6816150.7,202043.8 6816149,202061.3 6816148.3,202061 6816159.7,202060.8 6816168.4,202057.9 6816168.4,202048.4 6816168.3,202043.6 6816168.3))" );
	wkts.push_back( "POLYGON((970345.5 6386585.9,970341.3 6386592.9,970336 6386589.8,970339.6 6386582.8,970345.5 6386585.9))" );
	wkts.push_back( "POLYGON((24.881887 5.207295,24.918189 15.553369,41.363002 15.698577,41.181492 -1.036652,33.521766 -1.072954,33.412860 5.243597,24.881887 5.207295),(27.495632 13.847174,27.423028 6.768281,39.221183 6.913489,39.148579 14.101288,27.495632 13.847174))" );
	wkts.push_back( "MULTIPOLYGON(((1.600000 0.000000,1.200000 1.058300,0.800000 1.385640,0.400000 1.549190,0.000000 1.600000,-0.400000 1.549190,-0.800000 1.385640,-1.200000 1.058300,-1.600000 0.000000,-1.200000 -1.058300,-0.800000 -1.385640,-0.400000 -1.549190,0.000000 -1.600000,0.400000 -1.549190,0.800000 -1.385640,1.200000 -1.058300,1.600000 0.000000)),((3.600000 9.000000,3.200000 10.058300,2.800000 10.385640,2.400000 10.549190,2.000000 10.600000,1.600000 10.549190,1.200000 10.385640,0.800000 10.058300,0.400000 9.000000,0.800000 7.941700,1.200000 7.614360,1.600000 7.450810,2.000000 7.400000,2.400000 7.450810,2.800000 7.614360,3.200000 7.941700,3.600000 9.000000)),((8.600000 1.000000,8.212500 2.043960,7.825000 2.370900,7.437500 2.539020,7.050000 2.599220,6.662500 2.564000,6.275000 2.426320,5.887500 2.149930,5.500000 1.556780,5.376860 1.815020,5.253720 1.994070,5.130580 2.132160,5.007440 2.243000,4.884310 2.333420,4.761170 2.407350,4.638030 2.467280,4.514890 2.514890,4.395130 2.783340,4.275360 2.966150,4.155600 3.106610,4.035830 3.219450,3.916070 3.311800,3.796300 3.387770,3.676540 3.449930,3.556780 3.500000,3.676160 3.549890,3.795550 3.611800,3.914930 3.687410,4.034320 3.779270,4.153700 3.891410,4.273090 4.030850,4.392470 4.211950,4.511860 4.476280,4.772880 4.416200,5.033890 4.400360,5.294910 4.427410,5.555930 4.499690,5.816950 4.624280,6.077960 4.817630,6.338980 5.124140,6.600000 6.000000,6.211020 7.045680,5.822040 7.372680,5.433050 7.540280,5.044070 7.599390,4.655090 7.562380,4.266110 7.421760,3.877120 7.139800,3.488140 6.523720,3.227120 6.583800,2.966110 6.599640,2.705090 6.572590,2.444070 6.500310,2.183050 6.375720,1.922040 6.182370,1.661020 5.875860,1.400000 5.000000,1.530400 4.367320,1.660810 4.124470,1.791210 3.951750,1.921610 3.818020,2.052010 3.711080,2.182420 3.624660,2.312820 3.555080,2.443220 3.500000,2.312820 3.444920,2.182420 3.375340,2.052010 3.288920,1.921610 3.181980,1.791210 3.048250,1.660810 2.875530,1.530400 2.632680,1.400000 2.000000,1.535640 1.355290,1.671280 1.108650,1.806920 0.933910,1.942560 0.799250,2.078190 0.692230,2.213830 0.606460,2.349470 0.538220,2.485110 0.485110,2.861970 -0.124670,3.238830 -0.407350,3.615690 -0.553160,3.992560 -0.599980,4.369420 -0.556770,4.746280 -0.415300,5.123140 -0.139540,5.500000 0.443220,5.887500 -0.149930,6.275000 -0.426320,6.662500 -0.564000,7.050000 -0.599220,7.437500 -0.539020,7.825000 -0.370900,8.212500 -0.043960,8.600000 1.000000)))" ) ;

	for ( size_t i = 0; i < wkts.size(); i++ ){
		std::auto_ptr< Geometry > g( io::readWkt( wkts[i] ) );
		std::auto_ptr< Geometry > result( generator::building( *g, 10.0, 0.7 ) ) ;
		std::cout << "[" << i << "]" << result->asText(5) << std::endl ;

#ifdef SFCGAL_WITH_OSG
		std::ostringstream oss;
		oss << "building" << i << ".osg" ;
		io::osgWriteFile( *result, oss.str() );
#endif
	}

	return 0 ;
}
