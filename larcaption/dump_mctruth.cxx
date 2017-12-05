#include <iostream>
#include <string>

// ROOT headers
#include "TH2D.h"
#include "TCanvas.h"

// larlite headers
#include "DataFormat/mctrack.h"
#include "DataFormat/mcshower.h"

// larcv headers
#include "Base/PSet.h"
#include "Base/LArCVBaseUtilFunc.h"
#include "DataFormat/ImageMeta.h"
#include "DataFormat/Image2D.h"
#include "DataFormat/EventImage2D.h"

// larlitecv includes
#include "Base/DataCoordinator.h"

int main( int nargs, char** argv ) {
  
  std::cout << "Dump MC track/shower info" << std::endl;

  std::string cfg_file = argv[1];


  // parse configuration file
  // -------------------------
  // get file-level configuration parameter set
  larcv::PSet cfg = larcv::CreatePSetFromFile( cfg_file );
  // get main Parameter Set (PSet)
  larcv::PSet config = cfg.get<larcv::PSet>("DumpMCTruth");
  // get input filenames from PSet
  // larlite: holds data about particles, both truth and reconstructed
  std::string larlite_inputfile = config.get<std::string>("larliteInputFilename");
  // larcv: holds data pertaining to event image
  std::string larcv_inputfile   = config.get<std::string>("larcvInputFilename");
  // get name of trees that store mc track and mc shower info
  std::string mctrack_treename  = config.get<std::string>("MCTrackTree");
  std::string mcshower_treename = config.get<std::string>("MCShowerTree");
  // get name of trees that store larcv image object
  std::string image_treename    = config.get<std::string>("ImageTreeName");
  // do we also make an image of the data
  bool dump_images              = config.get<bool>("DumpImages");
  
  // Configure Data coordinator
  // --------------------------
  larlitecv::DataCoordinator dataco;


  // larlite
  dataco.add_inputfile( larlite_inputfile, "larlite" );
  // larcv
  dataco.add_inputfile( larcv_inputfile, "larcv" );

  // configure the data coordinator
  dataco.configure( cfg_file, "StorageManager", "IOManager", "DumpMCTruth" );
  
  // initialize
  dataco.initialize();

  // Start Event Loop
  int nentries = dataco.get_nentries("larcv");
  nentries = 10; // to shorten the loop

  
  for (int ientry=0; ientry<nentries; ientry++) {
    std::cout << "[Entry " << ientry << "]" << std::endl;

    // get the entry
    dataco.goto_entry(ientry,"larlite");

    // get the truth data for this event (from larlite file)
    larlite::event_mctrack*   mctrack_v = (larlite::event_mctrack*) dataco.get_larlite_data( larlite::data::kMCTrack,  mctrack_treename );
    larlite::event_mcshower* mcshower_v = (larlite::event_mcshower*)dataco.get_larlite_data( larlite::data::kMCShower, mcshower_treename );

    // get input images (from larcv file)
    larcv::EventImage2D* event_imgs    = (larcv::EventImage2D*)dataco.get_larcv_data( larcv::kProductImage2D, image_treename );
    // get array of images in this event
    const std::vector<larcv::Image2D>& img_v = event_imgs->Image2DArray();
    std::cout << "size of first image: " 
	      << " rows=" << img_v.at(0).meta().rows()
	      << " cols=" << img_v.at(0).meta().cols() 
	      << std::endl;


    // loop through the mc tracks and dump some information
    std::cout << "///// MCTrack objects ////////////////////////////////////////////" << std::endl;
    int itrack = 0;
    for ( auto const& track : *mctrack_v ) {
      std::cout << "[Track " << itrack << "]" << std::endl;      
      std::cout << "  track unique ID: " << track.TrackID() << std::endl;
      std::cout << "  track mother ID: " << track.MotherTrackID() << std::endl;
      std::cout << "  particle ID: " << track.PdgCode() << std::endl;
      std::cout << "  creation process of particle track: " << track.Process() << std::endl;
      std::cout << "  starting energy: " << track.Start().E() << std::endl;
      std::cout << "  starting 3-momentum: (" << track.Start().Px() << "," << track.Start().Py() << "," << track.Start().Pz() << ")" << std::endl;
      std::cout << "  starting 3-position: (" << track.Start().X() << "," << track.Start().Y() << "," << track.Start().Z() << ")" << std::endl;
      itrack++;
    }

    // loop through the mc shower and dump some information
    std::cout << "///// MCShower objects ////////////////////////////////////////////" << std::endl;
    int ishower = 0;
    for ( auto const& shower : *mcshower_v ) {
      std::cout << "[Shower " << ishower << "]" << std::endl;      
      std::cout << "  shower unique ID: " << shower.TrackID() << std::endl;
      std::cout << "  shower mother ID: " << shower.MotherTrackID() << std::endl;
      std::cout << "  particle ID: " << shower.PdgCode() << std::endl;
      std::cout << "  creation process of particle shower: " << shower.Process() << std::endl;
      std::cout << "  starting energy: " << shower.Start().E() << std::endl;
      std::cout << "  starting 3-momentum: (" << shower.Start().Px() << "," << shower.Start().Py() << "," << shower.Start().Pz() << ")" << std::endl;
      std::cout << "  starting 3-position: (" << shower.Start().X() << "," << shower.Start().Y() << "," << shower.Start().Z() << ")" << std::endl;
      ishower++;
    }

    // dump MicroBooNE LArTPC data to image
    // We copy data from Image2D object into ROOT 2D histogram and use it to draw an image and save it to png

    if ( dump_images ) {
      
      TCanvas canvas("c","",1000,500); // ROOT canvas object
      // loop through the event images: one per TPC wireplane
      
      // dimensions/coordinates of image (all images have the same dimensions)
      const larcv::ImageMeta& meta = img_v.front().meta();
      
      TH2D hist2d( "hist2d_tmp", "TPC data;wire number;time tick number", meta.cols(), meta.min_x(), meta.max_x(), meta.rows(), meta.min_y(), meta.max_y() );
      for ( size_t plane=0; plane<img_v.size(); plane++) {
	auto const& img = img_v.at(plane);
	// loop over pixel values and fill histogram
	// note: 1st histogram bin starts at index 1 (0 index histogram bin is the underflow)
	for (size_t row=0; row<meta.rows(); row++) {
	  // rows follow computer vision convention where (col,row) origin is in upper left of image
	  for (size_t col=0; col<meta.cols(); col++) {
	    hist2d.SetBinContent( col+1, meta.rows()-row-1, img.pixel(row,col) );
	  }
	}
	// we set the bounds of the values we will draw (to help contrast so that really big pixels do not dominate image)
	hist2d.SetMinimum(0);
	hist2d.SetMaximum(255); 
	hist2d.Draw("COLZ"); // use color scale for Z
	char zname[100];
	sprintf( zname, "img_entry%03d_plane%d.png", ientry, plane );
	canvas.Draw();
	canvas.SaveAs( zname );
      }
    }
    
  }
  
  dataco.finalize();
    

  
  return 0;
}
