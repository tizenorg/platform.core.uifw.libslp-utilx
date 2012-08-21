#sbs-git:slp/pkgs/l/libslp-utilx libslp-utilx 0.1.7 5957503c84e65113399e346c7d5618e73957d6ff
Name:       libslp-utilx
Summary:    utilX 
Version:    0.1.7
Release:    1.1
Group:      System/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

BuildRequires: cmake
BuildRequires: pkgconfig(libdri2)
BuildRequires: pkgconfig(dri2proto)
BuildRequires: pkgconfig(x11)
BuildRequires: pkgconfig(xext)
BuildRequires: pkgconfig(xv)
BuildRequires: pkgconfig(xdamage)
BuildRequires: pkgconfig(libdrm)
BuildRequires: pkgconfig(libdrm_slp)

%description
Utility functions for the XWindow


%package devel
Summary:    utilX
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
Utility functions for the XWindow (developement files)

%prep
%setup -q


%build
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%defattr(-,root,root,-)
/usr/lib/libutilX.so.*


%files devel
%defattr(-,root,root,-)
/usr/include/utilX.h
/usr/lib/libutilX.so
/usr/lib/pkgconfig/utilX.pc




