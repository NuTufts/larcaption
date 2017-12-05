#!/bin/bash

if [ -z ${LARCAPTION_BASEDIR+x} ]; then
    export LARCAPTION_BASEDIR=$PWD
fi

# setup environment variables
source $LARCAPTION_BASEDIR/setup.sh

# setup larlite
source $LARCAPTION_BASEDIR/larlite/config/setup.sh

# setup LArCV
source $LARCAPTION_BASEDIR/LArCV/configure.sh

# setup larlitecv
source $LARCAPTION_BASEDIR/larlitecv/configure.sh


