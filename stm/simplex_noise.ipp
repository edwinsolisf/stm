#include <algorithm>
#include <random>
#include "simplex_noise.h"

namespace stm
{
	template<uint32_t dimensions>
	simplex_noise<dimensions>::simplex_noise()
		:_seed(-1), _discontinuity_factor(0.6f), _floor(default_floor), _hash(default_hash),
		 _gradient_generator(default_gradient_generator), _normalize_scale(default_normalizer),
		 _permutations(GenRandomPermutations((uint32_t)::pow(2,8 + dimensions)))
	{
		static_assert(dimensions > 0, "Simplex_Noise cannot be generate noise for that dimension");
	}

	template<uint32_t dimensions>
	simplex_noise<dimensions>::simplex_noise(uint32_t seed, bool discontinuity,
								 bool fast_floor, std::function<uint32_t(uint32_t)> hash_function,
								 std::function<float(float)> normalize_function)
		:_seed(seed), _discontinuity_factor(0.6f), _floor(default_floor), _hash(hash_function),
		 _gradient_generator(default_gradient_generator), _normalize_scale(normalize_function),
		 _permutations(GenPermutations((uint32_t)::pow(2,8 + dimensions), seed))
	{
		static_assert(dimensions > 0, "Simplex_Noise cannot be generate noise for that dimension");
		if(!discontinuity) _discontinuity_factor = 0.5f;
		if(!fast_floor) _floor = ::floorf;
	}

	template<uint32_t dimensions>
	simplex_noise<dimensions>::simplex_noise(uint32_t seed, float discontinuity_factor, bool fast_floor,
								 std::function<stm::dynamic_vector<float>(int32_t, uint32_t, std::function<uint32_t(uint32_t)>)> 
								 gradient_generator_function,
								 std::function<float(float)> normalize_function)
		:_seed(seed), _discontinuity_factor(discontinuity_factor), _floor(default_floor), _hash(default_hash), 
		 _gradient_generator(gradient_generator_function), _normalize_scale(normalize_function),
		 _permutations(GenPermutations((uint32_t)::pow(2,8 + dimensions), seed))
	{
		static_assert(dimensions > 0, "Simplex_Noise cannot be generate noise for that dimension");
		if(!fast_floor) _floor = ::floorf;
	}

	template<uint32_t dimensions>
	float simplex_noise<dimensions>::Noise(const stm::vector<float, dimensions>& coordinates) const
	{
		//Take the coordinate and skew it
		const float skew_factor = (::sqrt((float)dimensions + 1.0f) - 1.0f) / (float)dimensions;
		stm::matrix<float, dimensions, dimensions> skew_matrix = stm::matrix<float, dimensions, dimensions>(skew_factor);
		stm::vector<float, dimensions> skewed_coordinate = coordinates + stm::multiply(skew_matrix, coordinates);

		//Get the nearest vertex in the skewed space
		stm::vector<float, dimensions> skewed_base_vertex_coordinate = skewed_coordinate;
		skewed_base_vertex_coordinate.ApplyToVector(_floor);

		//Unskew the coordinate of the vertex
		const float unskew_factor = (1.0f - (1.0f / ::sqrt(1.0f + (float)dimensions))) / (float)dimensions;
		stm::matrix<float, dimensions, dimensions> unskew_matrix = stm::matrix<float, dimensions, dimensions>(unskew_factor);
		stm::vector<float, dimensions> unskewed_base_vertex_coordinate = skewed_base_vertex_coordinate - stm::multiply(unskew_matrix, skewed_base_vertex_coordinate);

		//Calculate the distance to the unskewed position of the vertex
		stm::vector<float, dimensions> distance_to_base_vertex = coordinates - unskewed_base_vertex_coordinate;

		//Get the arrangement of the simplex vertices of the hypercube
		auto vertex_arrangement = GetVertexIndicesOrder(distance_to_base_vertex);
		stm::vector<float, dimensions> coordinate_traversal;

		//Calculate the noise value for each vertex
		float noise_value = 0.0f;
		for (uint32_t k = 0; k < dimensions + 1; ++k)
		{
			stm::vector<float, dimensions> vertex = distance_to_base_vertex - coordinate_traversal + stm::multiply(unskew_matrix, coordinate_traversal);
			noise_value += GetVertexNoiseValue(vertex, _discontinuity_factor, coordinate_traversal.template Cast<uint32_t>(),
				skewed_base_vertex_coordinate.template Cast<int32_t>());
			if (k != dimensions)
				coordinate_traversal[vertex_arrangement[k]] = 1.0f;
		}
		
		//Normalize between (-1, 1)
		return noise_value * _normalize_scale(_discontinuity_factor);
	}

	template<uint32_t dimensions>
	stm::dynamic_vector<float> simplex_noise<dimensions>::GenNoiseMap(const stm::vector<uint32_t, dimensions>& map_dimensions, float scale) const
	{
		uint32_t size = 1;
		for (uint32_t i = 0; i < dimensions; ++i)
			size *= map_dimensions[i];

		stm::dynamic_vector<float> map(size);
		for (uint32_t i = 0; i < size; ++i)
		{
			stm::vector<float, dimensions> in;
			in[0] = (float)(i%map_dimensions[0]);
			for(uint32_t j = 1; j < dimensions; ++j)
				in[j] = (float)((i / map_dimensions[j - 1]) % map_dimensions[j]);
			map[i] = Noise(in) * scale;
		}
		return map;
	}

	template<uint32_t dimensions>
	stm::vector<uint32_t, dimensions> simplex_noise<dimensions>::GetVertexIndicesOrder(const stm::vector<float, dimensions>& internal_coordinates) const
	{
		stm::vector<uint32_t, dimensions> out, sorted(-1);
		auto sorted_coordinates = internal_coordinates;
		std::sort(sorted_coordinates.begin(), sorted_coordinates.end());
		for (uint32_t i = 0; i < internal_coordinates.GetSize(); ++i)
		{
			auto it = std::upper_bound(sorted_coordinates.cbegin(), sorted_coordinates.cend(), internal_coordinates[i]);
			uintptr_t offset = it - sorted_coordinates.cbegin();
			
			if (it - 1 != std::lower_bound(sorted_coordinates.cbegin(), sorted_coordinates.cend(), internal_coordinates[i]))
			{
				uintptr_t t = 1;
				while (std::find(sorted.cbegin(), sorted.cend(), offset - t) != sorted.cend())
					t++;
				sorted[i] = offset - t;
			}
			else
			{
				sorted[i] = offset - 1;
			}
		}

		for (uint32_t i = 0; i < dimensions; ++i)
			out[dimensions - 1 - sorted[i]] = i;
		return out;
	}

	template<uint32_t dimensions>
	float simplex_noise<dimensions>::GetVertexNoiseValue(const stm::vector<float, dimensions>& vertex, float discontinuity_factor, const stm::vector<uint32_t, dimensions>& indices, const stm::vector<int32_t, dimensions>& base_coordinate) const
	{
		float out = discontinuity_factor - vertex.DotProduct(vertex);
		if (out > 0.0f) out = ::pow(out, 4);
		else return 0.0f;
		out *= GradientDotProduct(PermutationIndices(indices, base_coordinate), vertex);
		return out;
	}

	template<uint32_t dimensions>
	float simplex_noise<dimensions>::GradientDotProduct(int32_t permutation, const stm::vector<float, dimensions> vertex) const
	{
		if (dimensions > 2)
		{
			auto gradient = _gradient_generator(permutation, dimensions, _hash);
			return vertex.DotProduct(gradient);
		}
		stm::vector<float, dimensions> gradient(_gradient_generator(permutation, 3, _hash).GetData());
		return vertex.DotProduct(gradient);
	}

	template<uint32_t dimensions>
	int32_t simplex_noise<dimensions>::PermutationIndices(const stm::vector<uint32_t, dimensions> indices, const stm::vector<int32_t, dimensions>& base_coordinate) const
	{
		uint32_t index = indices[dimensions - 1] + base_coordinate[dimensions - 1];
		index %= _permutations.GetSize();
		int32_t val = _permutations[index];
		for (uint32_t i = 1; i < dimensions; ++i)
		{
			index = base_coordinate[dimensions - 1 - i] + indices[dimensions - 1 - i] + val;
			index %= _permutations.GetSize();
			val = _permutations[index];
		}
		return val;
	}

	template<uint32_t dimensions>
	stm::dynamic_vector<uint32_t> simplex_noise<dimensions>::GenPermutations(uint32_t size, uint32_t seed)
	{
		stm::dynamic_vector<uint32_t> out(size);
		for (uint32_t i = 0; i < size; ++i)
			out[i] = i;
		auto rng = std::default_random_engine{ seed };
		std::shuffle(out.begin(), out.end(), rng);
		return out;
	}

	template<uint32_t dimensions>
	stm::dynamic_vector<uint32_t> simplex_noise<dimensions>::GenRandomPermutations(uint32_t size)
	{
		stm::dynamic_vector<uint32_t> out(size);
		for (uint32_t i = 0; i < size; ++i)
			out[i] = i;
		
		std::random_device rd;
		auto rng = std::default_random_engine{ rd() };
		std::shuffle(out.begin(), out.end(), rng);
		return out;
	}

	template<uint32_t dimensions>
	inline float simplex_noise<dimensions>::default_floor(float value)
	{
		return value >= 0.f? (float)(int32_t)value : (float)((int32_t)value - 1);
	}

	template<uint32_t dimensions>
	inline float simplex_noise<dimensions>::default_normalizer(float discontinuity_factor)
	{
		return dimensions > 2 ? 1.089f/(::pow(8.0f * discontinuity_factor / 9.0f, 4) * ::sqrt(((float)dimensions - 1.0f) * discontinuity_factor / 9.0f)) :
			   dimensions > 1 ? 24.5f : 27.7f;
	}

	template<uint32_t dimensions>
	uint32_t simplex_noise<dimensions>::default_hash(uint32_t value)
	{
		//From adler hash function
		const uint32_t hash_mod = 65521;
		const uint8_t* ptr = (uint8_t*)&value;
		uint32_t value1 = 1, value2 = 0;
		for (size_t i = 0; i < sizeof(uint32_t); ++i)
		{
			value1 = (value1 + ptr[i]) % hash_mod;
			value2 = (value1 + value2) % hash_mod;
		}
		return (value2 << 16) | value1;
	}

	template<uint32_t dimensions>
	stm::dynamic_vector<float> simplex_noise<dimensions>::default_gradient_generator(int32_t original, uint32_t dim,
		std::function<uint32_t(uint32_t)> hash)
	{

		stm::dynamic_vector<float> out(dim);
		int32_t signs = hash(original) & ((int32_t)::pow(2, dim) - 1);
		int32_t zeroPivot = GetEdgeDirection(original, dim, hash);
		for (uint32_t i = 0; i < dim; ++i)
		{
			if (i == zeroPivot)
			{
				out[i] = 0.f;
				continue;
			}
			out[i] = (GetSignDirection(signs, i) ? -1.0f : 1.0f);
		}
		return out;
	}

	template<uint32_t dimensions>
	int32_t simplex_noise<dimensions>::GetEdgeDirection(int32_t original, uint32_t dim, std::function<uint32_t(uint32_t)> hash)
	{
		int32_t bits = 0;
		int32_t val = original;
		for (int32_t i = 0; i < dim; ++i)
		{
			bits += CountBits(val);
			val = hash(hash(val));
		}
		return bits % dim;
	}

	template<uint32_t dimensions>
	int32_t simplex_noise<dimensions>::CountBits(int32_t val)
	{
		uint32_t count = 0;
		for (uint32_t i = 0; i < sizeof(int32_t) * 8; ++i)
			if (val & (1 << i)) count++;
		return count;
	}

	template<uint32_t dimensions>
	inline bool simplex_noise<dimensions>::GetSignDirection(int32_t original, uint32_t dim)
	{
		return original & (1 << (dim));
	}
}