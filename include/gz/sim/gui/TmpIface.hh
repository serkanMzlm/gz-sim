/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef GZ_GAZEBO_GUI_TMPIFACE_HH_
#define GZ_GAZEBO_GUI_TMPIFACE_HH_

#ifndef Q_MOC_RUN
  #include <gz/gui/qt.h>
#endif

#include <gz/msgs.hh>
#include <gz/transport.hh>

#include "gz/sim/Export.hh"

namespace ignition
{
  namespace gazebo
  {
    /// \brief Temporary place to prototype transport interfaces while it's not
    /// clear where they will live.
    ///
    /// Move API from here to their appropriate locations once that's known.
    ///
    /// This class should be removed before releasing!
    class IGNITION_GAZEBO_VISIBLE TmpIface : public QObject
    {
      Q_OBJECT

      /// \brief Constructor: advertize services and topics
      public: TmpIface();

      /// \brief Destructor
      public: ~TmpIface() override = default;

      /// \brief Callback when user asks to start a new world.
      /// This is the client-side logic which requests the server_control
      /// service.
      public slots: void OnNewWorld();

      /// \brief Callback when user asks to load a world file.
      /// This is the client-side logic which requests the server_control
      /// service.
      /// \param[in] _path Path to world file.
      public slots: void OnLoadWorld(const QString &_path);

      /// \brief Callback when user asks to save a world file providing a path.
      /// This is the client-side logic which requests the server_control
      /// service.
      /// \param[in] _path Path to world file.
      public slots: void OnSaveWorldAs(const QString &_path);

      /// \brief This function does nothing and is kept only for retaining ABI
      /// compatibility. /server_control service handling was moved to
      /// ServerPrivate.
      /// \param[in] _req Request
      /// \param[out] _res Response
      /// \return False.
      private: bool IGN_DEPRECATED(3) OnServerControl(
        const msgs::ServerControl &_req, msgs::Boolean &_res);

      /// \brief Communication node
      private: transport::Node node;

      /// \brief Publisher
      private: transport::Node::Publisher worldStatsPub;
    };
  }
}
#endif
