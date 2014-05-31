# Build Projects in Order
cd ../rendering-framework
MSBuild.exe ./Framework.sln
cd ../engine
MSbuild.exe ./engine.sln
cd ../game
MSBuild.exe ./Game.sln

# Resources Prep 
mkdir -Force ../game/Debug/resources

cp ../rendering-framework/Debug/*.dll ../engine/Debug
cp ../engine/Debug/*.dll ../game/Debug

cp ../rendering-framework/Debug/*.cso ../engine/Debug
cp ../engine/Debug/*.cso ../game/Debug/resources/

cp ../rendering-framework/SampleApp/*.fbx ../engine/SampleApp/
cp ../rendering-framework/SampleApp/*.dds ../engine/SampleApp/
cp ../rendering-framework/SampleApp/*.obj ../engine/SampleApp/
cp ../rendering-framework/SampleApp/*.trk ../engine/SampleApp/

cp ../rendering-framework/SampleApp/*.fbx ../game/resources/
cp ../rendering-framework/SampleApp/*.dds ../game/resources/
cp ../rendering-framework/SampleApp/*.obj ../game/resources/
cp ../rendering-framework/SampleApp/*.trk ../game/resources/

cp ../game/resources/* ../game/Debug/resources/
