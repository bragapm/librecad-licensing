#pragma once

namespace Config {

// Alamat server Directus. Ubah di sini saat pindah ke server lain.
inline constexpr const char *kDefaultBaseUrl = "http://localhost:8055";

// Nama role admin di Directus (huruf besar-kecil tidak berpengaruh).
inline constexpr const char *kAdminRoleName = "Administrator";

} // namespace Config
