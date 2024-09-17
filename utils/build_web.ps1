# Make the script fail on any error
$ErrorActionPreference = "Stop"

# Get the parent directory of the current script
$parentDir = (Get-Item -Path $PSScriptRoot).Parent.FullName

# Go to the parent directory
Set-Location $parentDir

# Create or clear build-web directory
$buildDir = "build-web"
if (Test-Path $buildDir) {
    Remove-Item -Recurse -Force $buildDir
}
New-Item -ItemType Directory -Path $buildDir

# Go to build-web directory
Set-Location $buildDir

# Call emcmake cmake -G Ninja ..
emcmake cmake -G Ninja ..

# Call cmake --build .
cmake --build .

# Call emrun .\EcsSampleProject.html
emrun .\EcsSampleProject.html