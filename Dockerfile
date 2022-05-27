ARG BASE=cginternals/cpp-base:latest
ARG BASE_DEV=cginternals/cpp-base:dev
ARG CPPLOCATE_DEPENDENCY=cginternals/cpplocate:latest
ARG CPPFS_DEPENDENCY=cginternals/cppfs:latest
ARG CPPASSIST_DEPENDENCY=cginternals/cppassist:latest
ARG PROJECT_NAME=cppexpose

# DEPENDENCIES

FROM $CPPLOCATE_DEPENDENCY AS cpplocate

FROM $CPPFS_DEPENDENCY AS cppfs

FROM $CPPASSIST_DEPENDENCY AS cppassist

# BUILD

FROM $BASE_DEV AS build

ARG PROJECT_NAME
ARG COMPILER_FLAGS="-j 4"

COPY --from=cpplocate $WORKSPACE/cpplocate $WORKSPACE/cpplocate
COPY --from=cppfs $WORKSPACE/cppfs $WORKSPACE/cppfs
COPY --from=cppassist $WORKSPACE/cppassist $WORKSPACE/cppassist

ENV cpplocate_DIR="$WORKSPACE/cpplocate"
ENV cppfs_DIR="$WORKSPACE/cppfs"
ENV cppassist_DIR="$WORKSPACE/cppassist"
ENV cppexpose_DIR="$WORKSPACE/$PROJECT_NAME"

WORKDIR $WORKSPACE/$PROJECT_NAME

ADD cmake cmake
ADD docs docs
ADD deploy deploy
ADD source source
ADD CMakeLists.txt CMakeLists.txt
ADD configure configure
ADD $PROJECT_NAME-config.cmake $PROJECT_NAME-config.cmake
ADD $PROJECT_NAME-logo.png $PROJECT_NAME-logo.png
ADD $PROJECT_NAME-logo.svg $PROJECT_NAME-logo.svg
ADD LICENSE LICENSE
ADD README.md README.md
ADD AUTHORS AUTHORS

RUN ./configure
RUN CMAKE_OPTIONS="-DOPTION_BUILD_TESTS=Off" ./configure
RUN cmake --build build -- $COMPILER_FLAGS

# INSTALL

FROM build as install

ARG PROJECT_NAME

WORKDIR $WORKSPACE/$PROJECT_NAME

RUN CMAKE_OPTIONS="-DCMAKE_INSTALL_PREFIX=$WORKSPACE/$PROJECT_NAME-install" ./configure
RUN cmake --build build --target install

# DEPLOY

FROM $BASE AS deploy

ARG PROJECT_NAME

COPY --from=build $WORKSPACE/cpplocate $WORKSPACE/cpplocate
COPY --from=build $WORKSPACE/cppfs $WORKSPACE/cppfs
COPY --from=build $WORKSPACE/cppassist $WORKSPACE/cppassist

COPY --from=install $WORKSPACE/$PROJECT_NAME-install $WORKSPACE/$PROJECT_NAME

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$WORKSPACE/cpplocate/lib
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$WORKSPACE/cppfs/lib
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$WORKSPACE/cppassist/lib
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$WORKSPACE/$PROJECT_NAME/lib
