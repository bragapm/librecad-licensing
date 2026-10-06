import QtQuick
import QtQml
import LicensingPortalContent

// App.qml hanya mengatur halaman mana yang tampil.
// Semua logic ada di ViewModel C++ (LoginViewModel, AppViewModel).
Window {
    id: window
    width: 1100
    height: 680
    minimumWidth: 480
    minimumHeight: 600

    visible: true
    title: "LicensingPortal"

    Loader {
        anchors.fill: parent
        sourceComponent: {
            switch (AppViewModel.currentPage) {
            case "userDashboard":
                return userDashboardPage
            case "adminDashboard":   // TODO: ganti ke adminDashboardPage kalau sudah dibuat
                return adminDashboardPage
            default:
                return loginPage
            }
        }
    }

    // ---------------- Halaman login ----------------
    Component {
        id: loginPage

        LoginScreen {
            id: loginScreen
            busy: LoginViewModel.isLoading

            // Tampilkan pesan error dari ViewModel
            Binding {
                target: loginScreen.errorText
                property: "text"
                value: LoginViewModel.errorMessage
            }

            // Salin isi field ke ViewModel
            Connections {
                target: loginScreen.usernameField
                function onTextChanged() { LoginViewModel.email = loginScreen.usernameField.text }
                function onAccepted() { loginScreen.passwordField.forceActiveFocus() }
            }
            Connections {
                target: loginScreen.passwordField
                function onTextChanged() { LoginViewModel.password = loginScreen.passwordField.text }
                function onAccepted() { LoginViewModel.submit() }
            }

            // Aksi tombol
            Connections {
                target: loginScreen.loginButton
                function onClicked() { LoginViewModel.submit() }
            }
            Connections {
                target: loginScreen.forgotButton
                function onClicked() { console.log("Forgot password clicked") }
            }
        }
    }

    // ---------------- Dashboard user ----------------
    Component {
        id: userDashboardPage

        UserDashboard {
            id: dashboard
            welcomeText: qsTr("Halo, ") + AppViewModel.userEmail

            licenseModel: UserDashboardViewModel.licenseModel

            Component.onCompleted: {
                UserDashboardViewModel.refresh()
            }

            Connections {
                target: dashboard.logoutButton
                function onClicked() { AppViewModel.logout() }
            }
            Connections {
                target: dashboard.buyButton
                function onClicked() {
                    console.log("Beli Lisensi diklik")   // TODO: pindah ke UserDashboardViewModel
                }
            }
        }
    }
}
