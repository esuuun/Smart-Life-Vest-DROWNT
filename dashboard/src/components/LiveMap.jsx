import React, { useEffect, useRef } from 'react';
import { MapContainer, TileLayer, Marker, Popup, Polyline, useMap } from 'react-leaflet';
import L from 'leaflet';
import { Navigation, MapPin, Radio, Satellite } from 'lucide-react';

// Komponen pembantu untuk otomatis menganimasikan pusat peta ke posisi korban terbaru
function MapReCenter({ position }) {
  const map = useMap();
  useEffect(() => {
    if (position && position[0] && position[1]) {
      map.panTo(position, { animate: true, duration: 0.8 });
    }
  }, [position, map]);
  return null;
}

// Buat custom marker icon dengan SVG radar pulse
function createCustomMarker(status) {
  const isCrit = status === 'KRITIS';
  const isWarn = status === 'WASPADA';
  const color = isCrit ? '#BF3711' : isWarn ? '#D9822B' : '#288661';
  const glow = isCrit ? 'rgba(191,55,17,0.5)' : isWarn ? 'rgba(217,130,43,0.4)' : 'rgba(40,134,97,0.4)';

  return L.divIcon({
    className: 'custom-sar-marker',
    html: `
      <div style="position: relative; width: 32px; height: 32px; display: flex; align-items: center; justify-content: center;">
        <div style="
          position: absolute;
          width: 32px;
          height: 32px;
          border-radius: 50%;
          background: ${color};
          opacity: 0.3;
          animation: pulse-crit 1.6s infinite;
        "></div>
        <div style="
          width: 16px;
          height: 16px;
          border-radius: 50%;
          background: ${color};
          border: 2px solid #FFFFFF;
          box-shadow: 0 0 12px ${glow};
          z-index: 2;
        "></div>
      </div>
    `,
    iconSize: [32, 32],
    iconAnchor: [16, 16]
  });
}

export default function LiveMap({ telemetry, breadcrumbs, onSetPresetLocation, theme = 'light' }) {
  const currentPos = [telemetry.latitude, telemetry.longitude];
  const markerIcon = createCustomMarker(telemetry.status);

  // 100% Bebas API Key (Open-Source OpenStreetMap & Esri World Street Map)
  const tileUrl = 'https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png';

  return (
    <div className="card" style={{ padding: 0, overflow: 'hidden', display: 'flex', flexDirection: 'column', height: '100%' }}>
      {/* Map Header Bar */}
      <div style={{
        padding: '0.85rem 1.25rem',
        borderBottom: '1px solid var(--border-subtle)',
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'space-between',
        background: 'var(--bg-surface)'
      }}>
        <div style={{ display: 'flex', alignItems: 'center', gap: '0.65rem' }}>
          <Navigation size={18} color="var(--primary-sage)" />
          <span style={{ fontSize: '0.825rem', fontWeight: 700, textTransform: 'uppercase', letterSpacing: '0.06em', color: 'var(--text-primary)' }}>
            Live GPS SAR Locator (NEO-M8N)
          </span>
        </div>

        {/* GPS Satellite & Coordinates Metadata */}
        <div style={{ display: 'flex', alignItems: 'center', gap: '1rem', fontSize: '0.75rem' }}>
          <div style={{ display: 'flex', alignItems: 'center', gap: '0.35rem', color: 'var(--text-secondary)' }}>
            <Satellite size={14} color="var(--accent-mint)" />
            <span>Sats: <strong className="font-mono" style={{ color: 'var(--text-primary)' }}>{telemetry.satellites}</strong></span>
          </div>

          <div className="font-mono" style={{
            background: 'var(--bg-app)',
            padding: '0.25rem 0.65rem',
            borderRadius: '4px',
            border: '1px solid var(--border-subtle)',
            color: 'var(--accent-mint)'
          }}>
            {telemetry.latitude.toFixed(6)}, {telemetry.longitude.toFixed(6)}
          </div>
        </div>
      </div>

      {/* Interactive Leaflet Map Canvas */}
      <div style={{ flex: 1, minHeight: '380px', position: 'relative' }}>
        <MapContainer
          center={currentPos}
          zoom={17}
          scrollWheelZoom={true}
          style={{ width: '100%', height: '100%', minHeight: '380px' }}
        >
          {/* 100% Free & Open-Source OpenStreetMap Tile Layer (Zero API Key) */}
          <TileLayer
            key={tileUrl}
            attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
            url={tileUrl}
          />

          {/* Breadcrumb trajectory polyline */}
          {breadcrumbs.length > 1 && (
            <Polyline
              positions={breadcrumbs}
              pathOptions={{
                color: telemetry.status === 'KRITIS' ? '#BF3711' : '#288661',
                weight: 3,
                opacity: 0.8,
                dashArray: '4, 8'
              }}
            />
          )}

          {/* Victim Marker */}
          <Marker position={currentPos} icon={markerIcon}>
            <Popup>
              <div style={{ fontSize: '0.8rem', lineHeight: 1.4, color: 'var(--text-primary)' }}>
                <strong style={{ color: telemetry.status === 'KRITIS' ? '#BF3711' : '#1B5141' }}>
                  {telemetry.id} — {telemetry.status}
                </strong>
                <br />
                Risk: {telemetry.riskScore}% | SpO2: {telemetry.spo2}% | HR: {telemetry.heartRate} BPM
                <br />
                Lat: {telemetry.latitude.toFixed(5)}, Lng: {telemetry.longitude.toFixed(5)}
              </div>
            </Popup>
          </Marker>

          <MapReCenter position={currentPos} />
        </MapContainer>

        {/* Quick Location Presets Overlay (Atas Kanan Peta) */}
        <div style={{
          position: 'absolute',
          top: '12px',
          right: '12px',
          zIndex: 999,
          background: 'var(--bg-surface-glass)',
          backdropFilter: 'blur(8px)',
          padding: '0.4rem 0.6rem',
          borderRadius: 'var(--radius-sm)',
          border: '1px solid var(--border-medium)',
          display: 'flex',
          alignItems: 'center',
          gap: '0.4rem'
        }}>
          <span style={{ fontSize: '0.7rem', color: 'var(--text-muted)', fontWeight: 600 }}>Demo Locations:</span>
          <button
            onClick={() => onSetPresetLocation(-6.3627, 106.8272)}
            className="btn btn-outline"
            style={{ padding: '0.2rem 0.5rem', fontSize: '0.675rem' }}
          >
            Danau UI
          </button>
          <button
            onClick={() => onSetPresetLocation(-6.1158, 106.8155)}
            className="btn btn-outline"
            style={{ padding: '0.2rem 0.5rem', fontSize: '0.675rem' }}
          >
            Pantai Ancol
          </button>
          <button
            onClick={() => onSetPresetLocation(-5.8500, 106.5800)}
            className="btn btn-outline"
            style={{ padding: '0.2rem 0.5rem', fontSize: '0.675rem' }}
          >
            P. Seribu
          </button>
        </div>
      </div>
    </div>
  );
}
