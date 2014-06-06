# Build Projects in Order
cd ../rendering-framework
MSBuild.exe ./Framework.sln /m
cd ../engine
MSbuild.exe ./engine.sln /m
cd ../game
MSBuild.exe ./Game.sln /m

# Resources Prep 
mkdir -Force ../game/Debug/resources

cp ../rendering-framework/Debug/*.dll ../engine/Debug
cp ../engine/Debug/*.dll ../game/Debug

cp ../rendering-framework/Debug/*.cso ../engine/Debug
cp ../engine/Debug/*.cso ../game/Debug/resources/

cp ../game/game-core/resources/*.ini ../game/Debug/resources