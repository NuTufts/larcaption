# LArCaption

Skeleton program to develop how to convert simulation truth information about the particle interaction into a graph-representable caption.

## Building

I am going to assume Meitner. It will have a copy of ROOT, which should be the only dependency. Meitner will also have test data files to run on.

* go to some directory where you want to clone the repository.  I am going to assume `~/working/larbys`
* clone the repository

    git clone https://github.com/NuTufts/larcaption.git

* initiate the submodules and pull their code. (what is a submodule? I often refer to this [page](https://chrisjean.com/git-submodules-adding-using-removing-and-updating/) for descriptions and code snippets.)

    git submodule init
    git submodule update

* configure your bash shell with the right environment variables.  you need to do this every time you work with this code in a new shell instance.

    source configure.sh


* build the code. you only need to do this when you've made a change (or updated) the submodule repositories (larcv, larlite, larlitecv).

    source build.sh

* go to the larcaption code folder


    cd larcaption


* build the sandbox program


    make


that's it for building. you should see an executable binary `dump_mctruth` in the larcaption folder.


## Running

First, one must setup the program parameters which are kept in a config file.
An example file, `config.cfg` is in the larcaption program folder.
It might look like the following:


```
DumpMCTruth: {

  # larcv manager configuration
  IOManager: {
    Verbosity: 2 #  2=normal 1=more info 0=debug/bar
    IOMode: 0 # read/write (saving muon track clusters)
    InputFiles: []
    InputDirs: []
    ReadOnlyDataType: [0]
    ReadOnlyDataName: ["wire"]
  }

  # larlite manager configuratino
  StorageManager: {
    IOMode: 0 # read-only for now
    ReadOnlyProducers: []
    ReadOnlyDataTypes: []
    WriteOnlyDataTypes: []
    WriteOnlyProducers: []
  }

  # example file on meitner machine @ /media/hdd1/larbys/larcaption_example_data
  larliteInputFilename: "/media/hdd1/larbys/larcaption_example_data/"
  larcvInputFilename: "/media/hdd1/larbys/larcaption_example_data/"
  MCTrackTree: "mcreco"
  MCShowerTree: "mcreco"
  ImageTreeName: "wire"
  DumpImages: true
}
```

The parameters are:

* `larliteInputFilename`: path to the file that contains the mc truth information
* `larcvInputFilename`: path to the file that contains the corresponding lar tpc image data
* `MCTrackTree`: name of the ROOT `TTree` instance saved in the larlite ROOT file that keeps the list of track-like particles (muon, proton, pions)
* `MCShowerTree`: name of the ROOT `TTree` instane saved in the larlite ROOT file that keeps the list of shower-like particles (eletrons, photons)
* `ImageTreeName`: name of the ROOT `TTree` instane saved in the larcv ROOT file that keeps the image data
* `DumpImages`: if true will dump pngs of the images

To first start out, you probably only need to worry about the path to the input data files and whether or not you want to dump pngs of the images.

## Developing

Go ahead and edit `dump_mctruth.cxx`. When you want to build, just type make in the larcaption program folder.


## Steps (just a draft)


* understand/familiarize what the different functions in  `dump_mctruth.cxx` are doing
* understand the data products being taken from the file: `mctrack`, `mcshower`, `image2d`. The headers for these objects can be found in
  * larlite/core/DataFormat: mctrack, mcshower
  * larcv/core/DataFormat: image2d
* make sure only neutrino particles are being dumped (use the origin flag in the mctrack/mcshower data products)
* note: if you want to know what the pdg codes are, refer [here](http://home.fnal.gov/~mrenna/lutp0613man2/node44.html)
* store the neutrino particles into a graph
* convert graph into a caption
* convert caption into a graph
* need a way to save caption into a larcv datafile (when we get to here to we can think about how to do this.)