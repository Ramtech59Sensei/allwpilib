// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc2/command/button/JoystickButton.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();

  // Set up default drive command
  m_drive.SetDefaultCommand(frc2::RunCommand(
      [this] {
        m_drive.ArcadeDrive(-m_driverController.GetLeftY(),
                            m_driverController.GetRightX());
      },
      {&m_drive}));
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here

  // Spin up the shooter when the 'A' button is pressed
  frc2::JoystickButton(&m_driverController, frc::XboxController::Button::kA)
      .OnTrue(&m_spinUpShooter);

  // Turn off the shooter when the 'B' button is pressed
  frc2::JoystickButton(&m_driverController, frc::XboxController::Button::kB)
      .OnTrue(&m_stopShooter);

  // Shoot when the 'X' button is held
  frc2::JoystickButton(&m_driverController, frc::XboxController::Button::kX)
      .OnTrue(&m_shoot)
      .OnFalse(&m_stopFeeder);

  // While holding the shoulder button, drive at half speed
  frc2::JoystickButton(&m_driverController,
                       frc::XboxController::Button::kRightBumper)
      .OnTrue(&m_driveHalfSpeed)
      .OnFalse(&m_driveFullSpeed);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Runs the chosen command in autonomous
  return m_autonomousCommand.get();
}
