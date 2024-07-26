use crate::datatypes;

use super::RotationAxisAngle;

impl RotationAxisAngle {
    /// Create a new rotation from an axis and an angle.
    #[inline]
    pub fn new(axis: impl Into<datatypes::Vec3D>, angle: impl Into<datatypes::Angle>) -> Self {
        Self(datatypes::RotationAxisAngle::new(axis, angle))
    }
}

#[cfg(feature = "glam")]
impl From<RotationAxisAngle> for glam::Affine3A {
    #[inline]
    fn from(val: RotationAxisAngle) -> Self {
        Self::from_axis_angle(val.0.axis.into(), val.0.angle.radians())
    }
}

#[cfg(feature = "mint")]
impl From<RotationAxisAngle> for mint::Quaternion<f32> {
    #[inline]
    fn from(rotation: RotationAxisAngle) -> Self {
        rotation.0.into()
    }
}
