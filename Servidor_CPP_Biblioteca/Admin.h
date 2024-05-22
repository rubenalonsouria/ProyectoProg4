#ifndef ADMIN_H_
#define ADMIN_H_
#include <string>
class Admin {
	std:: string nombre;
	std:: string apellido;
	std:: string dni;
	std:: string numTarjeta;
	std:: string contrasenya;
public:
	Admin();
	Admin(const std::string& n, const std::string& a, const std::string& d, const std::string& nt, const std::string& c);
	const std:: string& getNombre()const;
	const std:: string& getApellido()const;
	const std:: string& getDni()const;
	const std:: string& getNumTarjeta()const;
	const std:: string& getContrasenya()const;
	virtual ~Admin();
};

#endif /* ADMIN_H_ */
