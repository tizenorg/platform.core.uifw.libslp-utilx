Name:       libslp-utilx
Summary:    utilX
Version:    0.1.23
Release:    1.1
Group:      UI Framework/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: 	libslp-utilx.manifest

BuildRequires: cmake
BuildRequires: pkgconfig(libdri2)
BuildRequires: pkgconfig(dri2proto)
BuildRequires: pkgconfig(x11)
BuildRequires: pkgconfig(xext)
BuildRequires: pkgconfig(xv)
BuildRequires: pkgconfig(xdamage)
BuildRequires: pkgconfig(xrandr)
BuildRequires: pkgconfig(libdrm)
BuildRequires: pkgconfig(libtbm)

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
cp %{SOURCE1001} .


%build
%cmake .


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

# for license notification
mkdir -p %{buildroot}/usr/share/license
cp %{_builddir}/%{buildsubdir}/LICENSE.APLv2 %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%defattr(-,root,root,-)
%{_libdir}/libutilX.so.*
/usr/share/license/%{name}

%files devel
%manifest %{name}.manifest
%defattr(-,root,root,-)
/usr/include/utilX.h
%{_libdir}/libutilX.so
%{_libdir}/pkgconfig/utilX.pc




