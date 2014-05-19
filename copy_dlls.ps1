# Debug Prep 
mkdir -Force ../game/Debug/resources

cp ../rendering-framework/Debug/*.dll ../engine/Debug
cp ../engine/Debug/*.dll ../game/Debug

cp ../rendering-framework/Debug/*.cso ../engine/Debug
cp ../rendering-framework/Debug/defaultVertex.cso ../game/Debug
cp ../rendering-framework/Debug/defaultPixel.cso ../game/Debug

cp ../engine/Debug/*.cso ../game/Debug/resources/

cp ../rendering-framework/SampleApp/*.fbx ../engine/SampleApp/
cp ../rendering-framework/SampleApp/*.dds ../engine/SampleApp/
cp ../rendering-framework/SampleApp/*.obj ../engine/SampleApp/
cp ../rendering-framework/SampleApp/*.trk ../engine/SampleApp/

cp ../rendering-framework/SampleApp/*.fbx ../game/Debug/resources/
cp ../rendering-framework/SampleApp/*.dds ../game/Debug/resources/
cp ../rendering-framework/SampleApp/*.obj ../game/Debug/resources/
cp ../rendering-framework/SampleApp/*.trk ../game/Debug/resources/

# Release Prep
#mkdir -Force ../game/Release/resources

#cp ../rendering-framework/Release/*.dll ../engine/Release
#cp ../engine/Release/*.dll ../game/Release
#
#cp ../rendering-framework/Release/*.cso ../engine/Release
#cp ../engine/Release/*.cso ../game/Release
#
#cp ../rendering-framework/SampleApp/*.fbx ../engine/SampleApp/
#cp ../rendering-framework/SampleApp/*.dds ../engine/SampleApp/
#cp ../rendering-framework/SampleApp/*.obj ../engine/SampleApp/
#cp ../rendering-framework/SampleApp/*.trk ../engine/SampleApp/
#
#cp ../rendering-framework/SampleApp/*.fbx ../game/Release/resources/
#cp ../rendering-framework/SampleApp/*.dds ../game/Release/resources/
#cp ../rendering-framework/SampleApp/*.obj ../game/Debug/resources/
#cp ../rendering-framework/SampleApp/*.trk ../game/Debug/resources/