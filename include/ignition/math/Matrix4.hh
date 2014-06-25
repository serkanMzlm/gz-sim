/*
 * Copyright (C) 2012-2014 Open Source Robotics Foundation
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
#ifndef _IGNITION_MATRIX4_HH_
#define _IGNITION_MATRIX4_HH_

#define _USE_MATH_DEFINES
#include <cmath>

#include <ignition/math/AffineException.hh>
#include <ignition/math/Matrix3.hh>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Pose3.hh>

namespace ignition
{
  namespace math
  {
    /// \class Matrix4 Matrix4.hh ignition/math.hh
    /// \brief A 4x4 matrix class
    template<typename T>
    class IGNITION_HIDDEN Matrix4
    {
      /// \brief Identity matrix
      public: static const Matrix4<T> Identity;

      /// \brief Zero matrix
      public: static const Matrix4<T> Zero;

      /// \brief Constructor
      public: Matrix4()
      {
        memset(this->data, 0, sizeof(this->data[0][0])*16);
      }

      /// \brief Copy constructor
      /// \param _m Matrix to copy
      public: Matrix4(const Matrix4<T> &_m)
      {
        memcpy(this->data, _m.data, sizeof(this->data[0][0])*16);
      }

      /// \brief Constructor
      /// \param[in] _v00 Row 0, Col 0 value
      /// \param[in] _v01 Row 0, Col 1 value
      /// \param[in] _v02 Row 0, Col 2 value
      /// \param[in] _v03 Row 0, Col 3 value
      /// \param[in] _v10 Row 1, Col 0 value
      /// \param[in] _v11 Row 1, Col 1 value
      /// \param[in] _v12 Row 1, Col 2 value
      /// \param[in] _v13 Row 1, Col 3 value
      /// \param[in] _v20 Row 2, Col 0 value
      /// \param[in] _v21 Row 2, Col 1 value
      /// \param[in] _v22 Row 2, Col 2 value
      /// \param[in] _v23 Row 2, Col 3 value
      /// \param[in] _v30 Row 3, Col 0 value
      /// \param[in] _v31 Row 3, Col 1 value
      /// \param[in] _v32 Row 3, Col 2 value
      /// \param[in] _v33 Row 3, Col 3 value
      public: Matrix4(T _v00, T _v01, T _v02, T _v03,
                      T _v10, T _v11, T _v12, T _v13,
                      T _v20, T _v21, T _v22, T _v23,
                      T _v30, T _v31, T _v32, T _v33)
      {
        this->Set(_v00, _v01, _v02, _v03,
                  _v10, _v11, _v12, _v13,
                  _v20, _v21, _v22, _v23,
                  _v30, _v31, _v32, _v33);
      }

      /// \brief Construct Matrix4 from a quaternion.
      /// \param[in] _q Quaternion.
      public: Matrix4(const Quaternion<T> &_q)
      {
        Quaternion<T> qt = _q;
        qt.Normalize();
        this->Set(1 - 2*qt.y()*qt.y() - 2 *qt.z()*qt.z(),
                  2 * qt.x()*qt.y() - 2*qt.z()*qt.w(),
                  2 * qt.x() * qt.z() + 2 * qt.y() * qt.w(),
                  0,

                  2 * qt.x() * qt.y() + 2 * qt.z() * qt.w(),
                  1 - 2*qt.x()*qt.x() - 2 * qt.z()*qt.z(),
                  2 * qt.y() * qt.z() - 2 * qt.x() * qt.w(),
                  0,

                  2 * qt.x() * qt.z() - 2 * qt.y() * qt.w(),
                  2 * qt.y() * qt.z() + 2 * qt.x() * qt.w(),
                  1 - 2 * qt.x()*qt.x() - 2 * qt.y()*qt.y(),
                  0,

                  0, 0, 0, 1);
      }

      /// \brief Destructor
      public: virtual ~Matrix4() {}

      /// \brief Change the values
      /// \param[in] _v00 Row 0, Col 0 value
      /// \param[in] _v01 Row 0, Col 1 value
      /// \param[in] _v02 Row 0, Col 2 value
      /// \param[in] _v03 Row 0, Col 3 value
      /// \param[in] _v10 Row 1, Col 0 value
      /// \param[in] _v11 Row 1, Col 1 value
      /// \param[in] _v12 Row 1, Col 2 value
      /// \param[in] _v13 Row 1, Col 3 value
      /// \param[in] _v20 Row 2, Col 0 value
      /// \param[in] _v21 Row 2, Col 1 value
      /// \param[in] _v22 Row 2, Col 2 value
      /// \param[in] _v23 Row 2, Col 3 value
      /// \param[in] _v30 Row 3, Col 0 value
      /// \param[in] _v31 Row 3, Col 1 value
      /// \param[in] _v32 Row 3, Col 2 value
      /// \param[in] _v33 Row 3, Col 3 value
      public: void Set(
            T _v00, T _v01, T _v02, T _v03,
            T _v10, T _v11, T _v12, T _v13,
            T _v20, T _v21, T _v22, T _v23,
            T _v30, T _v31, T _v32, T _v33)
      {
        this->data[0][0] = _v00;
        this->data[0][1] = _v01;
        this->data[0][2] = _v02;
        this->data[0][3] = _v03;

        this->data[1][0] = _v10;
        this->data[1][1] = _v11;
        this->data[1][2] = _v12;
        this->data[1][3] = _v13;

        this->data[2][0] = _v20;
        this->data[2][1] = _v21;
        this->data[2][2] = _v22;
        this->data[2][3] = _v23;

        this->data[3][0] = _v30;
        this->data[3][1] = _v31;
        this->data[3][2] = _v32;
        this->data[3][3] = _v33;
      }

      /// \brief Set the translational values [ (0, 3) (1, 3) (2, 3) ]
      /// \param[in] _t Values to set
      public: void SetTranslate(const Vector3<T> &_t)
      {
        this->data[0][3] = _t.x();
        this->data[1][3] = _t.y();
        this->data[2][3] = _t.z();
      }

      /// \brief Set the translational values [ (0, 3) (1, 3) (2, 3) ]
      /// \param[in] _x X translation value.
      /// \param[in] _y Y translation value.
      /// \param[in] _z Z translation value.
      public: void SetTranslate(T _x, T _y, T _z)
      {
        this->data[0][3] = _x;
        this->data[1][3] = _y;
        this->data[2][3] = _z;
      }

      /// \brief Get the translational values as a Vector3
      /// \return x,y,z translation values
      public: Vector3<T> GetTranslation() const
      {
        return Vector3<T>(this->data[0][3], this->data[1][3], this->data[2][3]);
      }

      /// \brief Get the scale values as a Vector3<T>
      /// \return x,y,z scale values
      public: Vector3<T> GetScale() const
      {
        return Vector3<T>(this->data[0][0], this->data[1][1], this->data[2][2]);
      }

      /// \brief Get the rotation as a quaternion
      /// \return the rotation
      public: Quaternion<T> GetRotation() const
      {
        Quaternion<T> q;
        /// algorithm from Ogre::Quaternion<T> source, which in turn is based on
        /// Ken Shoemake's article "Quaternion<T> Calculus and Fast Animation".
        T trace = this->data[0][0] + this->data[1][1] + this->data[2][2];
        T root;
        if (trace > 0)
        {
          root = sqrt(trace + 1.0);
          q.w(root / 2.0);
          root = 1.0 / (2.0 * root);
          q.x((this->data[2][1] - this->data[1][2]) * root);
          q.y((this->data[0][2] - this->data[2][0]) * root);
          q.z((this->data[1][0] - this->data[0][1]) * root);
        }
        else
        {
          static unsigned int s_iNext[3] = {1, 2, 0};
          unsigned int i = 0;
          if (this->data[1][1] > this->data[0][0])
            i = 1;
          if (this->data[2][2] > this->data[i][i])
            i = 2;
          unsigned int j = s_iNext[i];
          unsigned int k = s_iNext[j];

          root = sqrt(this->data[i][i] - this->data[j][j] -
                      this->data[k][k] + 1.0);

          T a, b, c;
          a = root / 2.0;
          root = 1.0 / (2.0 * root);
          b = (this->data[j][i] + this->data[i][j]) * root;
          c = (this->data[k][i] + this->data[i][k]) * root;

          switch (i)
          {
            case 0: q.x(a); break;
            case 1: q.y(a); break;
            case 2: q.z(a); break;
            default: break;
          };
          switch (j)
          {
            case 0: q.x(b); break;
            case 1: q.y(b); break;
            case 2: q.z(b); break;
            default: break;
          };
          switch (k)
          {
            case 0: q.x(c); break;
            case 1: q.y(c); break;
            case 2: q.z(c); break;
            default: break;
          };

          q.w((this->data[k][j] - this->data[j][k]) * root);
        }

        return q;
      }

      /// \brief Get the rotation as a Euler angles
      /// \param[in] _firstSolution True to get the first Euler solution,
      /// false to get the second.
      /// \return the rotation
      public: Vector3<T> GetEulerRotation(bool _firstSolution) const
      {
        Vector3<T> euler;
        Vector3<T> euler2;

        T m31 = this->data[2][0];
        T m11 = this->data[0][0];
        T m12 = this->data[0][1];
        T m13 = this->data[0][2];
        T m32 = this->data[2][1];
        T m33 = this->data[2][2];
        T m21 = this->data[1][0];

        if (std::abs(m31) >= 1.0)
        {
          euler.z(0.0);
          euler2.z(0.0);

          if (m31 < 0.0)
          {
            euler.y(M_PI / 2.0);
            euler2.y(M_PI / 2.0);
            euler.x(atan2(m12, m13));
            euler2.x(atan2(m12, m13));
          }
          else
          {
            euler.y(-M_PI / 2.0);
            euler2.y(-M_PI / 2.0);
            euler.x(atan2(-m12, -m13));
            euler2.x(atan2(-m12, -m13));
          }
        }
        else
        {
          euler.y(-asin(m31));
          euler2.y(M_PI - euler.y());

          euler.x(atan2(m32 / cos(euler.y()), m33 / cos(euler.y())));
          euler2.x(atan2(m32 / cos(euler2.y()), m33 / cos(euler2.y())));

          euler.z(atan2(m21 / cos(euler.y()), m11 / cos(euler.y())));
          euler2.z(atan2(m21 / cos(euler2.y()), m11 / cos(euler2.y())));
        }

        if (_firstSolution)
          return euler;
        else
          return euler2;
      }

      /// \brief Get the transformation as math::Pose
      /// \return the pose
      public: Pose3<T> GetAsPose() const
      {
        return Pose3<T>(this->GetTranslation(), this->GetRotation());
      }

      /// \brief Set the scale
      /// \param[in] _s scale
      public: void SetScale(const Vector3<T> &_s)
      {
        this->data[0][0] = _s.x();
        this->data[1][1] = _s.y();
        this->data[2][2] = _s.z();
        this->data[3][3] = 1.0;
      }

      /// \brief Set the scale
      /// \param[in] _x X scale value.
      /// \param[in] _y Y scale value.
      /// \param[in] _z Z scale value.
      public: void SetScale(T _x, T _y, T _z)
      {
        this->data[0][0] = _x;
        this->data[1][1] = _y;
        this->data[2][2] = _z;
        this->data[3][3] = 1.0;
      }

      /// \brief Return true if the matrix is affine
      /// \return true if the matrix is affine, false otherwise
      public: bool IsAffine() const
      {
        return equal(this->data[3][0], static_cast<T>(0)) &&
          equal(this->data[3][1], static_cast<T>(0)) &&
          equal(this->data[3][2], static_cast<T>(0)) &&
          equal(this->data[3][3], static_cast<T>(1));
      }

      /// \brief Perform an affine transformation
      /// \param _v Vector3 value for the transformation
      /// \return The result of the transformation
      /// \throws AffineException when matrix is not affine.
      public: Vector3<T> TransformAffine(const Vector3<T> &_v) const
      {
        if (!this->IsAffine())
          throw AffineException();

        return Vector3<T>(this->data[0][0]*_v.x() + this->data[0][1]*_v.y() +
                           this->data[0][2]*_v.z() + this->data[0][3],
                           this->data[1][0]*_v.x() + this->data[1][1]*_v.y() +
                           this->data[1][2]*_v.z() + this->data[1][3],
                           this->data[2][0]*_v.x() + this->data[2][1]*_v.y() +
                           this->data[2][2]*_v.z() + this->data[2][3]);
      }

      /// \brief Return the inverse matrix.
      /// This is a non-destructive operation.
      /// \return Inverse of this matrix.
      public: Matrix4<T> Inverse() const
      {
        T v0, v1, v2, v3, v4, v5, t00, t10, t20, t30;
        Matrix4<T> r;

        v0 = this->data[2][0]*this->data[3][1] -
          this->data[2][1]*this->data[3][0];
        v1 = this->data[2][0]*this->data[3][2] -
          this->data[2][2]*this->data[3][0];
        v2 = this->data[2][0]*this->data[3][3] -
          this->data[2][3]*this->data[3][0];
        v3 = this->data[2][1]*this->data[3][2] -
          this->data[2][2]*this->data[3][1];
        v4 = this->data[2][1]*this->data[3][3] -
          this->data[2][3]*this->data[3][1];
        v5 = this->data[2][2]*this->data[3][3] -
          this->data[2][3]*this->data[3][2];

        t00 = +(v5*this->data[1][1] -
            v4*this->data[1][2] + v3*this->data[1][3]);
        t10 = -(v5*this->data[1][0] -
            v2*this->data[1][2] + v1*this->data[1][3]);
        t20 = +(v4*this->data[1][0] -
            v2*this->data[1][1] + v0*this->data[1][3]);
        t30 = -(v3*this->data[1][0] -
            v1*this->data[1][1] + v0*this->data[1][2]);

        T invDet = 1 / (t00 * this->data[0][0] + t10 * this->data[0][1] +
            t20 * this->data[0][2] + t30 * this->data[0][3]);

        r(0, 0) = t00 * invDet;
        r(1, 0) = t10 * invDet;
        r(2, 0) = t20 * invDet;
        r(3, 0) = t30 * invDet;

        r(0, 1) = -(v5*this->data[0][1] -
            v4*this->data[0][2] + v3*this->data[0][3]) * invDet;
        r(1, 1) = +(v5*this->data[0][0] -
            v2*this->data[0][2] + v1*this->data[0][3]) * invDet;
        r(2, 1) = -(v4*this->data[0][0] -
            v2*this->data[0][1] + v0*this->data[0][3]) * invDet;
        r(3, 1) = +(v3*this->data[0][0] -
            v1*this->data[0][1] + v0*this->data[0][2]) * invDet;

        v0 = this->data[1][0]*this->data[3][1] -
          this->data[1][1]*this->data[3][0];
        v1 = this->data[1][0]*this->data[3][2] -
          this->data[1][2]*this->data[3][0];
        v2 = this->data[1][0]*this->data[3][3] -
          this->data[1][3]*this->data[3][0];
        v3 = this->data[1][1]*this->data[3][2] -
          this->data[1][2]*this->data[3][1];
        v4 = this->data[1][1]*this->data[3][3] -
          this->data[1][3]*this->data[3][1];
        v5 = this->data[1][2]*this->data[3][3] -
          this->data[1][3]*this->data[3][2];

        r(0, 2) = +(v5*this->data[0][1] -
            v4*this->data[0][2] + v3*this->data[0][3]) * invDet;
        r(1, 2) = -(v5*this->data[0][0] -
            v2*this->data[0][2] + v1*this->data[0][3]) * invDet;
        r(2, 2) = +(v4*this->data[0][0] -
            v2*this->data[0][1] + v0*this->data[0][3]) * invDet;
        r(3, 2) = -(v3*this->data[0][0] -
            v1*this->data[0][1] + v0*this->data[0][2]) * invDet;

        v0 = this->data[2][1]*this->data[1][0] -
          this->data[2][0]*this->data[1][1];
        v1 = this->data[2][2]*this->data[1][0] -
          this->data[2][0]*this->data[1][2];
        v2 = this->data[2][3]*this->data[1][0] -
          this->data[2][0]*this->data[1][3];
        v3 = this->data[2][2]*this->data[1][1] -
          this->data[2][1]*this->data[1][2];
        v4 = this->data[2][3]*this->data[1][1] -
          this->data[2][1]*this->data[1][3];
        v5 = this->data[2][3]*this->data[1][2] -
          this->data[2][2]*this->data[1][3];

        r(0, 3) = -(v5*this->data[0][1] -
            v4*this->data[0][2] + v3*this->data[0][3]) * invDet;
        r(1, 3) = +(v5*this->data[0][0] -
            v2*this->data[0][2] + v1*this->data[0][3]) * invDet;
        r(2, 3) = -(v4*this->data[0][0] -
            v2*this->data[0][1] + v0*this->data[0][3]) * invDet;
        r(3, 3) = +(v3*this->data[0][0] -
            v1*this->data[0][1] + v0*this->data[0][2]) * invDet;

        return r;
      }

      /// \brief Equal operator. this = _mat
      /// \param _mat Incoming matrix
      /// \return itself
      public: Matrix4<T> &operator=(const Matrix4<T> &_mat)
      {
        memcpy(this->data, _mat.data, sizeof(this->data[0][0])*16);
        return *this;
      }

      /// \brief Equal operator for 3x3 matrix
      /// \param _mat Incoming matrix
      /// \return itself
      public: const Matrix4<T> &operator=(const Matrix3<T> &_mat)
      {
        this->data[0][0] = _mat(0, 0);
        this->data[0][1] = _mat(0, 1);
        this->data[0][2] = _mat(0, 2);

        this->data[1][0] = _mat(1, 0);
        this->data[1][1] = _mat(1, 1);
        this->data[1][2] = _mat(1, 2);

        this->data[2][0] = _mat(2, 0);
        this->data[2][1] = _mat(2, 1);
        this->data[2][2] = _mat(2, 2);

        return *this;
      }

      /// \brief Multiplication operator
      /// \param _mat Incoming matrix
      /// \return This matrix * _mat
      public: Matrix4<T> operator*(const Matrix4<T> &_m2) const
      {
        return Matrix4<T>(
          this->data[0][0] * _m2(0, 0) +
          this->data[0][1] * _m2(1, 0) +
          this->data[0][2] * _m2(2, 0) +
          this->data[0][3] * _m2(3, 0),

          this->data[0][0] * _m2(0, 1) +
          this->data[0][1] * _m2(1, 1) +
          this->data[0][2] * _m2(2, 1) +
          this->data[0][3] * _m2(3, 1),

          this->data[0][0] * _m2(0, 2) +
          this->data[0][1] * _m2(1, 2) +
          this->data[0][2] * _m2(2, 2) +
          this->data[0][3] * _m2(3, 2),

          this->data[0][0] * _m2(0, 3) +
          this->data[0][1] * _m2(1, 3) +
          this->data[0][2] * _m2(2, 3) +
          this->data[0][3] * _m2(3, 3),

          this->data[1][0] * _m2(0, 0) +
          this->data[1][1] * _m2(1, 0) +
          this->data[1][2] * _m2(2, 0) +
          this->data[1][3] * _m2(3, 0),

          this->data[1][0] * _m2(0, 1) +
          this->data[1][1] * _m2(1, 1) +
          this->data[1][2] * _m2(2, 1) +
          this->data[1][3] * _m2(3, 1),

          this->data[1][0] * _m2(0, 2) +
          this->data[1][1] * _m2(1, 2) +
          this->data[1][2] * _m2(2, 2) +
          this->data[1][3] * _m2(3, 2),

          this->data[1][0] * _m2(0, 3) +
          this->data[1][1] * _m2(1, 3) +
          this->data[1][2] * _m2(2, 3) +
          this->data[1][3] * _m2(3, 3),

          this->data[2][0] * _m2(0, 0) +
          this->data[2][1] * _m2(1, 0) +
          this->data[2][2] * _m2(2, 0) +
          this->data[2][3] * _m2(3, 0),

          this->data[2][0] * _m2(0, 1) +
          this->data[2][1] * _m2(1, 1) +
          this->data[2][2] * _m2(2, 1) +
          this->data[2][3] * _m2(3, 1),

          this->data[2][0] * _m2(0, 2) +
          this->data[2][1] * _m2(1, 2) +
          this->data[2][2] * _m2(2, 2) +
          this->data[2][3] * _m2(3, 2),

          this->data[2][0] * _m2(0, 3) +
          this->data[2][1] * _m2(1, 3) +
          this->data[2][2] * _m2(2, 3) +
          this->data[2][3] * _m2(3, 3),

          this->data[3][0] * _m2(0, 0) +
          this->data[3][1] * _m2(1, 0) +
          this->data[3][2] * _m2(2, 0) +
          this->data[3][3] * _m2(3, 0),

          this->data[3][0] * _m2(0, 1) +
          this->data[3][1] * _m2(1, 1) +
          this->data[3][2] * _m2(2, 1) +
          this->data[3][3] * _m2(3, 1),

          this->data[3][0] * _m2(0, 2) +
          this->data[3][1] * _m2(1, 2) +
          this->data[3][2] * _m2(2, 2) +
          this->data[3][3] * _m2(3, 2),

          this->data[3][0] * _m2(0, 3) +
          this->data[3][1] * _m2(1, 3) +
          this->data[3][2] * _m2(2, 3) +
          this->data[3][3] * _m2(3, 3));
      }

      /// \brief Multiplication operator
      /// \param _vec Vector3
      /// \return Resulting vector from multiplication
      public: Vector3<T> operator*(const Vector3<T> &_vec) const
      {
        return Vector3<T>(
            this->data[0][0]*_vec.x() + this->data[0][1]*_vec.y() +
            this->data[0][2]*_vec.z() + this->data[0][3],
            this->data[1][0]*_vec.x() + this->data[1][1]*_vec.y() +
            this->data[1][2]*_vec.z() + this->data[1][3],
            this->data[2][0]*_vec.x() + this->data[2][1]*_vec.y() +
            this->data[2][2]*_vec.z() + this->data[2][3]);
      }

      /// \brief Get the value at the specified row, column index
      /// \param[in] _col The column index
      /// \param[in] _row the row index
      /// \return The value at the specified index
      public: inline const T &operator()(size_t _row, size_t _col) const
      {
        if (_row >= 4 || _col >= 4)
          throw IndexException();
        return this->data[_row][_col];
      }

      /// \brief Get a mutable version the value at the specified row,
      /// column index
      /// \param[in] _col The column index
      /// \param[in] _row The row index
      /// \return The value at the specified index
      public: inline T &operator()(size_t _row, size_t _col)
      {
        if (_row >= 4 || _col >= 4)
          throw IndexException();
        return this->data[_row][_col];
      }

      /// \brief Equality operator
      /// \param[in] _m Matrix3 to test
      /// \return true if the 2 matrices are equal (using the tolerance 1e-6),
      ///  false otherwise
      public: bool operator==(const Matrix4<T> &_m) const
      {
        return math::equal(this->data[0][0], _m(0, 0)) &&
               math::equal(this->data[0][1], _m(0, 1)) &&
               math::equal(this->data[0][2], _m(0, 2)) &&
               math::equal(this->data[0][3], _m(0, 3)) &&

               math::equal(this->data[1][0], _m(1, 0)) &&
               math::equal(this->data[1][1], _m(1, 1)) &&
               math::equal(this->data[1][2], _m(1, 2)) &&
               math::equal(this->data[1][3], _m(1, 3)) &&

               math::equal(this->data[2][0], _m(2, 0)) &&
               math::equal(this->data[2][1], _m(2, 1)) &&
               math::equal(this->data[2][2], _m(2, 2)) &&
               math::equal(this->data[2][3], _m(2, 3)) &&

               math::equal(this->data[3][0], _m(3, 0)) &&
               math::equal(this->data[3][1], _m(3, 1)) &&
               math::equal(this->data[3][2], _m(3, 2)) &&
               math::equal(this->data[3][3], _m(3, 3));
      }

      /// \brief Stream insertion operator
      /// \param _out output stream
      /// \param _m Matrix to output
      /// \return the stream
      public: friend std::ostream IGNITION_VISIBLE &operator<<(
                  std::ostream &_out, const ignition::math::Matrix4<T> &_m)
      {
        _out << precision(_m(0, 0), 6) << " "
             << precision(_m(0, 1), 6) << " "
             << precision(_m(0, 2), 6) << " "
             << precision(_m(0, 3), 6) << " "
             << precision(_m(1, 0), 6) << " "
             << precision(_m(1, 1), 6) << " "
             << precision(_m(1, 2), 6) << " "
             << precision(_m(1, 3), 6) << " "
             << precision(_m(2, 0), 6) << " "
             << precision(_m(2, 1), 6) << " "
             << precision(_m(2, 2), 6) << " "
             << precision(_m(2, 3), 6) << " "
             << precision(_m(3, 0), 6) << " "
             << precision(_m(3, 1), 6) << " "
             << precision(_m(3, 2), 6) << " "
             << precision(_m(3, 3), 6);

        return _out;
      }

      /// \brief Stream extraction operator
      /// \param _in input stream
      /// \param _pt Matrix4<T> to read values into
      /// \return the stream
      public: friend std::istream IGNITION_VISIBLE &operator>>(
                  std::istream &_in, ignition::math::Matrix4<T> &_m)
      {
        // Skip white spaces
        _in.setf(std::ios_base::skipws);
        T d[16];
        _in >> d[0] >> d[1] >> d[2] >> d[3]
            >> d[4] >> d[5] >> d[6] >> d[7]
            >> d[8] >> d[9] >> d[10] >> d[11]
            >> d[12] >> d[13] >> d[14] >> d[15];

        _m.Set(d[0], d[1], d[2], d[3],
               d[4], d[5], d[6], d[7],
               d[8], d[9], d[10], d[11],
               d[12], d[13], d[14], d[15]);
        return _in;
      }

      /// \brief The 4x4 matrix
      private: T data[4][4];
    };

    template<typename T>
    const Matrix4<T> Matrix4<T>::Identity(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);

    template<typename T>
    const Matrix4<T> Matrix4<T>::Zero(
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0);

    typedef Matrix4<int> Matrix4i;
    typedef Matrix4<double> Matrix4d;
    typedef Matrix4<float> Matrix4f;
  }
}
#endif
