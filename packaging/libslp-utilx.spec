%bcond_with x

Name:       libslp-utilx
Summary:    utilX
Version:    0.4.5
Release:    1
Group:      UI Framework/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz

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

%if !%{with x}
ExclusiveArch:
%endif

%description
Utility functions for the XWindow


%package devel
Summary:    utilX
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}
Requires:   pkgconfig(xproto)
Requires:   pkgconfig(x11)

%description devel
Utility functions for the XWindow (developement files)

%prep
%setup -q


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
%defattr(-,root,root,-)
%{_libdir}/libutilX.so.*
/usr/share/license/%{name}

%files devel
%defattr(-,root,root,-)
/usr/include/*
%{_libdir}/libutilX.so
%{_libdir}/pkgconfig/utilX.pc




