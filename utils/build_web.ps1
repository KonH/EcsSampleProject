# Make the script fail on any error
$ErrorActionPreference = "Stop"

# Get the parent directory of the current script
$parentDir = (Get-Item -Path $PSScriptRoot).Parent.FullName

# Create or clear build-web directory
$buildDir = Join-Path -Path $parentDir -ChildPath "build-web"
if (Test-Path $buildDir) {
    Remove-Item -Recurse -Force $buildDir
}
New-Item -ItemType Directory -Path $buildDir

# Call emcmake cmake -G Ninja
emcmake cmake -G Ninja -B $buildDir ..

# Call cmake --build
cmake --build $buildDir

# Call emrun .\EcsSampleProject.html
emrun $buildDir\EcsSampleProject.html